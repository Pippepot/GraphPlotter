#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Graph.h"

// Override base class with your custom functionality
class GraphPlotter : public olc::PixelGameEngine
{
	std::vector<Graph> graphs;

	olc::vf2d panOffset;
	float zoom;
	
	olc::vf2d oldMousePos;

public:
	GraphPlotter()
	{
		// Name you application
		sAppName = "GrafPlotter";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		panOffset = olc::vf2d(0, 0);
		zoom = 10;
		graphs.push_back(Graph("x"));
		graphs.push_back(Graph("l"));
		graphs.push_back(Graph("a"));
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::BLACK);

		// Pan is constant screen size

		// Mouse + pan = constant when panning

		// Pan
		olc::vf2d mousePos = olc::vf2d((float)GetMouseX() / ScreenWidth(), 1 - (float)GetMouseY() / ScreenHeight());

		if (GetMouse(0).bPressed)
			oldMousePos = mousePos;

		if (GetMouse(0).bHeld) {
			panOffset += (oldMousePos - mousePos) * zoom;

			oldMousePos = mousePos;
		}

		// Zoom
		if (GetMouseWheel() != 0) {
			float zoomAmount = zoom * (float)GetMouseWheel() / 500.0;
			zoom += zoomAmount;
			
			panOffset += (panOffset - ScreenSpaceToGraphSpace(GetMousePos())) * zoomAmount / zoom;
		}

		// Horizontal
		DrawString(GraphSpaceToPixelSpace(olc::vf2d(1, 0)),"1x", olc::WHITE);
		// Vertical
		DrawString(GraphSpaceToPixelSpace(olc::vf2d(0, 1)), "1y", olc::WHITE);

		DrawString(0, 0, std::to_string(zoom), olc::WHITE);
		DrawString(0, 20, std::to_string(ScreenSpaceToGraphSpaceX(GetMouseX())) + " " + std::to_string(ScreenSpaceToGraphSpaceY(GetMouseY())), olc::GREEN);
		DrawString(0, 40, std::to_string(panOffset.x) + " " + std::to_string(panOffset.y), olc::RED);

		float functionValue;
		float previousFunctionValue = 0;

		for (auto g : graphs) {
			for (int x = 0; x < ScreenWidth(); x++)
			{
				functionValue = GraphSpaceToPixelSpaceY(g.Calculate(ScreenSpaceToGraphSpaceX(x)));

				if (x == 0)
					previousFunctionValue = functionValue;

				DrawFunctionValuePixelSpace(x, functionValue, previousFunctionValue, olc::Pixel(g.r, g.b, g.g));
				previousFunctionValue = functionValue;

			}
		}


		// Draw lines
		// Horizontal panOffset.y * ScreenHeight() / zoom + 0.5 * ScreenHeight()
		DrawLine(0, GraphSpaceToPixelSpaceY(0), ScreenWidth(), GraphSpaceToPixelSpaceY(0), olc::WHITE);
		// Vertical
		DrawLine(GraphSpaceToPixelSpaceX(0), 0, GraphSpaceToPixelSpaceX(0), ScreenHeight(), olc::WHITE);

		return true;
	}

	void DrawFunctionValuePixelSpace(int x, int value, int previousValue, olc::Pixel pixel)
	{
		if (previousValue > ScreenHeight() || previousValue < 0)
			return;

		Draw(x, value, pixel);

		int difference = value - previousValue;

		// Graf goes down
		if (difference > 1) {
			for (int dy = 1; dy < difference; dy++)
			{
				Draw(x, previousValue + dy, pixel);
			}

			return;
		}

		// Graf goes up
		if (difference < -1) {
			for (int dy = -1; dy > difference; dy--)
			{
				Draw(x, previousValue + dy, pixel);
			}
			return;
		}

	}

	olc::vf2d GraphSpaceToPixelSpace(olc::vf2d point)
	{
		return olc::vf2d(GraphSpaceToPixelSpaceX(point.x), GraphSpaceToPixelSpaceY(point.y));
	}

	float GraphSpaceToPixelSpaceX(float x)
	{
		return ((x - panOffset.x) / zoom + 0.5)* ScreenWidth();
	}

	float GraphSpaceToPixelSpaceY(float y)
	{
		return ((panOffset.y - y) / zoom + 0.5) * ScreenHeight();
	}

	olc::vf2d ScreenSpaceToGraphSpace(olc::vf2d point)
	{
		return olc::vf2d(ScreenSpaceToGraphSpaceX(point.x), ScreenSpaceToGraphSpaceY(point.y));
	}

	float ScreenSpaceToGraphSpaceX(float x)
	{
		return (-0.5 * zoom + panOffset.x) + x * zoom / ScreenWidth();
	}

	float ScreenSpaceToGraphSpaceY(float y)
	{

		return (0.5 * zoom + panOffset.y) - y * zoom / ScreenHeight();
	}
};

int main()
{
	GraphPlotter plot;
	if (plot.Construct(256*4, 240*4, 1, 1))
		plot.Start();
	return 0;
}