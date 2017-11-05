#include "nwpwin.h"

class Static : public Window{
	std::string ClassName() { return "Static"; }
};

class MainWindow : public Window
{
	Static st;
	POINT currPos;
	int border;
protected:
	void OnLButtonDown(POINT p) {
		if (!st)
			st.Create(*this, WS_CHILD | WS_VISIBLE, ";)", NULL, p.x, p.y, 20, 20);
		SetWindowPos(st, NULL, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		currPos = p;
	};

	void OnKeyUp(int vk) {
		if (st){
			naCrtajGa(NULL);
		}
	}
	void OnKeyDown(int vk) {
		if (st)
		{
			int Speed = 5;
			if (GetKeyState(VK_LCONTROL) == -128)
				Speed = 20;

			switch (vk) {
			case (VK_LEFT) :
				currPos.x -= Speed;
				break;
			case (VK_RIGHT) :
				currPos.x += Speed;
				break;
			case (VK_UP) :
				currPos.y -= Speed;
				break;
			case(VK_DOWN) :
				currPos.y += Speed;
				break;
			default:
				return;
			}
			naCrtajGa(WS_BORDER);
		}
	}

	void naCrtajGa(int border){
		border = border;
		SetWindowLong(st, GWL_STYLE, WS_CHILD | WS_VISIBLE | border);
		SetWindowPos(st, NULL, currPos.x, currPos.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
	}

	void OnDestroy(){
		::PostQuitMessage(0);
	}
private:
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}