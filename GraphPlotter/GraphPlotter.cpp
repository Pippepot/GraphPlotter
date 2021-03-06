#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "GraphInput.h"
#include "Graph.h"
#include "GraphUtility.h"

// Override base class with your custom functionality
class GraphPlotter : public olc::PixelGameEngine
{
	std::vector<Graph> graphs;

	
	olc::vf2d oldMousePos;
	bool isDraggingMouse;

	const int inputBarSize = 64;


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
		graphWindowWidth = ScreenWidth();
		graphWindowHeight = ScreenHeight() - inputBarSize;

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

		FillRect(0, graphWindowHeight, graphWindowWidth, ScreenHeight(), olc::DARK_GREY);
		DrawString(10, graphWindowHeight + 10, inputString, olc::WHITE, 6);
		DrawLine(8 + cursor * 48, graphWindowHeight + 8, 8 + cursor * 48, ScreenHeight() - 8);


		// Pan
		olc::vf2d mousePos = olc::vf2d((float)GetMouseX() / graphWindowWidth, 1 - (float)GetMouseY() / graphWindowHeight);

		if (GetMouse(0).bReleased || mousePos.x > 0.99 || mousePos.x < 0.01 || mousePos.y > 0.99 || mousePos.y < 0.01)
		{
			isDraggingMouse = false;
		}

		if (GetMouse(0).bPressed) {
			oldMousePos = mousePos;
			isDraggingMouse = true;
		}

		if (isDraggingMouse) {
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
		// Horizontal
		olc::vf2d axes = GraphSpaceToPixelSpace(olc::vf2d(0, 0));

		if (axes.y < graphWindowHeight && axes.y > 0)
			DrawLine(0, axes.y, graphWindowWidth, axes.y, olc::WHITE);
		// Vertical
		if (axes.x < graphWindowWidth && axes.y > 0)
			DrawLine(axes.x, 0, axes.x, graphWindowHeight, olc::WHITE);

		

		return true;
	}

	void olc_UpdateKeyState(int32_t key, bool state) override
	{
		olc::PixelGameEngine::olc_UpdateKeyState(key, state);

		UpdateKeyState(key, state);
	}

	void DrawFunctionValuePixelSpace(int x, int value, int previousValue, olc::Pixel pixel)
	{
		if ((previousValue > graphWindowHeight || previousValue < 0) && (value > graphWindowHeight || value < 0))
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


};

int main()
{
	GraphPlotter plot;
	if (plot.Construct(256*4, 240*4, 1, 1))
		plot.Start();
	return 0;
}