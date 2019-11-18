//
// Created by brani on 24.10.2016.
//

#ifndef FVIZ_OBJ_MOUSE_H
#define FVIZ_OBJ_MOUSE_H


class Mouse {
public:
	void onLeftButton(int x, int y);
	void onRightButton(int x, int y);
	enum class State { None, Right, Left };

private:
	int xx = 0, xold = 0, xnew = 0;
	int yy = 0, yold = 0, ynew = 0;
	int zz = 0, zold = 0, znew = 0;
	State state = State::None;
public:
	int getXnew() const;
	int getYnew() const;
	int getZnew() const;
	State getState() const;
	void setXx(int xx);
	void setXold(int xold);
	void setYy(int yy);
	void setYold(int yold);
	void setZz(int zz);
	void setZold(int zold);
	void setState(State state);

};


#endif //FVIZ_OBJ_MOUSE_H
