// EvansAdventure.cpp : Defines the entry point for the console application.
//
#include "curses.h"
#include <cstdint>
#include <memory>
#include <vector>
#include <Windows.h>

//coordinates
//up = higher numbers, down = lower numbers
//left = lower numbers, right = higher numbers

WINDOW *map_window;
WINDOW *character_window;
WINDOW *buff_window;
WINDOW *text_window;
WINDOW *command_window;

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
	WINDOW *local;
	local = newwin(height, width, starty, startx);
	box(local, 0, 0);
	wrefresh(local);
	return local;
}

void refresh_border(WINDOW * win)
{
	box(win, 0, 0);
	wrefresh(win);
}

void buildui()
{
	int maxy, maxx;
	getmaxyx(stdscr, maxy, maxx);


	map_window = create_newwin(15, 40, 1, 0);
	buff_window = create_newwin(3, 40, 16, 0);

}

struct Position
{
	Position() : Position(0, 0) {}
	Position(int64_t nx, int64_t ny) : x(nx), y(ny) {}
	int64_t x;
	int64_t y;
};

struct Box
{
	Position UL;
	Position LR;
	int64_t Height() const { return UL.y - LR.y; }
	int64_t Width() const { return LR.x - UL.x; }
};

class Player
{
public:
	Position p;
	char m_Representation;
};

struct Wall
{
	Position start;
	Position stop;
};

class Room
{
public:
	Room();
	void AddWall(Wall& wall);
	char CharacterAt(int64_t x, int64_t y) const;
private:
	void normalize();
	std::vector<Wall> m_Walls;
	Box m_BoundingBox;
};

class World
{
public:
	World() {}
	bool IsBlocked(int64_t x, int64_t y) const;
	char CharacterAt(int64_t x, int64_t y) const;
	void Update(double dt);
	
	struct RoomInstance
	{
		Position p;
		Room room;
	};
private:

};



class Component
{
public:
	void Update(double dt);
};

class Renderable : public Component
{

};

class Movable : public Component
{

};


void game_loop(Player *p, int ch);
void erase(int y, int x) {
	mvaddch(y, x, '.');
}




int main()
{

	Player p;
	initscr();
	clear();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
	scrollok(stdscr, TRUE);

	buildui();
	
	int ch = getch();

	clear();

	game_loop(&p, ch);
	
	endwin();
	return 0;
}

void game_loop(Player *p, int ch)
{
 	if(ch == 'q' || ch =='Q') return;

	// Show the main character on the screen
	/*mvaddch(p->m_Y, p->m_X, p->m_Representation);*/
	nodelay(stdscr, TRUE);
	for(;;) {
		ch = wgetch(stdscr);
		
		refresh_border(map_window);
		refresh_border(buff_window);
		
		//if(ch == KEY_LEFT || ch == 'a' || ch == 'A') {
		//	erase(p->m_Y, p->m_X);
		//	p->m_X = p->m_X - 1;
		//	mvaddch(p->m_Y, p->m_X, p->m_Representation);
		//	refresh();
		//}
		//else if(ch == KEY_RIGHT || ch == 'd' || ch == 'D') {
		//	erase(p->m_Y, p->m_X);
		//	p->m_X = p->m_X + 1;
		//	mvaddch(p->m_Y, p->m_X, p->m_Representation);
		//	refresh();
		//}
		//else if(ch == KEY_UP || ch == 'w' || ch == 'W') {
		//	erase(p->m_Y, p->m_X);
		//	p->m_Y = p->m_Y - 1;
		//	mvaddch(p->m_Y, p->m_X, p->m_Representation);
		//	refresh();
		//}
		//else if(ch == KEY_DOWN || ch == 's' || ch == 'S') {
		//	erase(p->m_Y, p->m_X);
		//	p->m_Y = p->m_Y + 1;
		//	mvaddch(p->m_Y, p->m_X, p->m_Representation);
		//	refresh();
		//}
		if (ch == ERR)
		{
			//printw("nothing ready");
		}
		if(ch == 27 || ch == 'q' || ch == 'Q') {
			break;
		}
		
	}
}


