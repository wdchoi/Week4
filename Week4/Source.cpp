#include <GLFW/glfw3.h>
#include "math.h"
#include <iostream>


//class Line {
//public :
//	int start_x, start_y;
//	int end_x, end_y;
//	void draw() {
//
//	}
//};




const int width = 640;
const int height = 480;

//color = (Red, Green, Blue)
float *pixels = new float[width * height * 3];
//float *pixels = (float*)malloc(sizeof(float)*width*height * 3);
void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	if (i1 > i0) {
		if (j1 >= j0) {
			for (int i = i0; i <= i1; i++)
			{
				const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

				drawPixel(i, j, red, green, blue);
			}
		}
		else {
			for (int i = i0; i <= i1; i++)
			{
				const int j = j0 - (j0 - j1)*(i - i0) / (i1 - i0);

				drawPixel(i, j, red, green, blue);
			}
		}
	}
	else if (i1 < i0) {
		if (j1 >= j0) {
			for (int i = i1; i <= i0; i++)
			{
				const int j = j1 - (j1 - j0)*(i - i1) / (i0 - i1);
				drawPixel(i, j, red, green, blue);
			}
		}
		else {
			for (int i = i1; i <= i0; i++)
			{
				const int j = j1 + (j0 - j1)*(i - i1) / (i0 - i1);

				drawPixel(i, j, red, green, blue);
			}
		}
	}
	else {
		for (int j = j0; j <= j1; j++) {
			drawPixel(i0, j, 1.0f, 0.0f, 0.0f);
		}
	}
}
void drawLine2(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(j, i, red, green, blue);

	}
}


void drawThickerLine()
{
	int i_center = 50, j_center = 375;
	const int thinkness1 = 5;
	const int thinkness2 = 5;
	for (int k = 0; k < 10; k++) {

		for (int j = j_center - thinkness1; j < j_center + thinkness1; j++)
			for (int i = i_center - thinkness2; i < i_center + thinkness2; i++) {
				drawPixel(i, j, 1.0f, 0.0f, 0.0f);
			}
		i_center += 5;
		j_center += 5;

	}
}
class Geometry {
public:
	virtual void draw() {
		std::cout << "fdsf" << std::endl;
	}
	/*virtual void draw() = 0;
*/
};



class Line : public Geometry
{
private:
	int start_x, start_y;
	int end_x, end_y;
public:
	/*Line(const int& _start_x, const int & _start_y, const int& _end_x, const int& _end_y) {
		start_x = _start_x;
		start_y = _start_y;
		end_x = _end_x;
		end_y = _end_y;
	}*/
	void initialize(const int& _start_x, const int & _start_y, const int& _end_x, const int& _end_y) {
		start_x = _start_x;
		start_y = _start_y;
		end_x = _end_x;
		end_y = _end_y;
	}
	/*void printThisPointer() {
		std::cout << this << std::endl;
	}
	void drawSecondFunction() {

	}*/
	void draw() {
		/*this->drawSecondFunction();*/
		drawLine(start_x, start_y, end_x, end_y, 0.0f, 0.0f, 1.0f);
	}
};

class Box : public Geometry {
public:
	int center_x, center_y;
	int x_edge, y_edge;
	/*int left_bottom_x, left_bottom_y;
	int right_up_x, right_down_y;*/
	void initialize(const int& _c_x, const int& _c_y, const int&_e_x, const int&_e_y) {
		center_x = _c_x;
		center_y = _c_y;
		x_edge = _e_x;
		y_edge = _e_y;

	}
	void draw() {
		drawLine(center_x- x_edge/2, center_y- y_edge/2, center_x + x_edge / 2, center_y - y_edge / 2, 0.0f, 0.0f, 1.0f);
		drawLine(center_x + x_edge / 2, center_y - y_edge / 2, center_x + x_edge / 2, center_y + y_edge / 2, 0.0f, 0.0f, 1.0f);
		drawLine(center_x - x_edge / 2, center_y + y_edge / 2, center_x + x_edge / 2, center_y + y_edge / 2,  0.0f, 0.0f, 1.0f);
		drawLine(center_x - x_edge / 2, center_y - y_edge / 2, center_x - x_edge / 2, center_y + y_edge / 2, 0.0f, 0.0f, 1.0f);
	}
};
const int num_object = 2;
Geometry **my_objexts = new Geometry*[num_object];


const int num_lines = 10;
Line *my_lines = new Line[num_lines];
const int num_boxes = 3;
Box *box_list = new Box[num_boxes];




void initializeObject() {
	/*my_objexts[0] = new Line(0,0,100,100);*/
	my_objexts[0] = new Line;
	Line *temp = new Line;
	temp->initialize(0, 0, 100, 100);
	my_objexts[0] =temp;


	my_objexts[1] = new Box;
	Box *temp = new Box;
	temp->initialize(200, 200, 100, 100);
	my_objexts[1] = temp;

	for (int i = 0; i < num_lines; i++) {
		my_lines[i].initialize(100 * i + 10, 10, 100 * i + 50, 50);
		my_lines[i].draw();
	}

	for (int i = 0; i < num_boxes; i++) {
		box_list[i].initialize(200 * i, 200, 100, 100);
		box_list[i].draw();
	}
}

void draw() {


	/*drawLine(200, 450, 300, 450, 0.0f, 0.0f, 1.0f);
	drawLine(200, 350, 300, 350, 0.0f, 0.0f, 1.0f);
	drawLine2(350, 200, 450, 200, 0.0f, 0.0f, 1.0f);
	drawLine2(350, 300, 450, 300, 0.0f, 0.0f, 1.0f);*/



	/*drawLine(20, 100, 80, 200, 0.0f, 0.0f, 1.0f);
	drawLine(80, 200, 140, 100, 0.0f, 0.0f, 1.0f);
	drawLine(20, 100, 140, 100, 0.0f, 0.0f, 1.0f);*/


	//
	

	/*const int num_lines = 10;
	Line *my_lines = new Line[num_lines];*/

	/*for (int i = 0; i < num_lines; i++) {
		my_lines[i].start_x = 100 * i + 10;
		my_lines[i].start_y = 10;

		my_lines[i].end_x = 100 * i + 50;
		my_lines[i].end_y = 50;
		my_lines[i].draw();
	}*/
	/*first_line.draw();
	second_line.draw();
	third_line.draw();*/


	const int num_boxes = 3;
	Box *box_list = new Box[num_boxes];

	for (int i = 0; i < num_boxes; i++) {
		box_list[i].initialize(200*i, 200, 100, 100);
		box_list[i].draw();
	}
	Box first_box;
	first_box.initialize(200, 200, 100, 100);
	first_box.draw();


	/*drawLine(250, 150, 300, 200, 0.0f, 0.0f, 1.0f);
	drawLine(300, 200, 350, 150, 0.0f, 0.0f, 1.0f);
	drawLine(250, 150, 275, 100, 0.0f, 0.0f, 1.0f);
	drawLine(275, 100, 325, 100, 0.0f, 0.0f, 1.0f);
	drawLine(325, 100, 350, 150, 0.0f, 0.0f, 1.0f);*/
}


void drawcircle(const int x, const int y, const int r, const float& red, const float& green, const float& blue)
{
	int x_c = x;
	int y_c = y;


	for (int a = 0; a <= 2 * r; a++)
	{
		for (int b = 0; b <= 2 * r; b++)
		{
			int f = (r - b)*(r - b) + (r - a)*(r - a) - r*r;
			if (f < 0 && -200 < f)
			{
				drawPixel(x - r + b, y - r + a, 255, 0, 0);
			}
		}
	}
}
void drawEmptySquare() {

	const int i_center = 480, j_center = 400;
	const int thinkness = 50;

	for (int k = 0; k < 5; k++) {

		for (int j = j_center - thinkness; j < j_center + thinkness; j++)
			for (int i = i_center - thinkness; i < i_center + thinkness; i++) {
				drawPixel(i, j, 1.0f, 0.0f, 0.0f);
			}
	}


}


class Geometry {//mother class 
public:
	virtual void draw()
	{


		std::cout << "Drawing a Geometry" << std::endl;
	}
};

class ChildGeometry1 : public Geometry {
public:
	/*void function(const int a);
	void function(const int a, int b, int c);*/
	void draw() {//over-roading(don't missuse over-loading)


		Geometry::draw();
		ChildGeometry1::draw();
		this->draw();
		std::cout << "Drawing a Child Geometry" << std::endl;
	}
};
class ChildGeometry2 : public Geometry {
public:
	/*void function(const int a);
	void function(const int a, int b, int c);*/
	void draw() {//over-roading(don't missuse over-loading)
		std::cout << "Drawing a Child Geometry2" << std::endl;
	}
};

void(*fun_ptr)(void)= nullptr;



class printer {
public:
	void(printer::*fun_ptr)(void) = nullptr;
	void print() {
		std::cout << "fdsaf" << std::endl;
	}
};

int main(void)
{
	printer p;
	p.fun_ptr = &printer::print;
	((&p)->*p.fun_ptr)();
	/*fun_ptr = &print;

	(*fun_ptr)();*/
	exit(1);
	//Geometry *my_geometry = new Geometry;
	//my_geometry->draw();

	//Geometry *my_child = new ChildGeometry1;
	//my_child->draw();


	////polymorphism(this is what we do abstraction)
	//Geometry **my_geometry_list = new Geometry* [4];
	//my_geometry_list[0] = new Geometry;
	//my_geometry_list[1] = new ChildGeometry1;
	//my_geometry_list[2] = new ChildGeometry2;
	//my_geometry_list[3] = new Geometry;
	//for (int i = 0; i < 4; i++) {
	//	my_geometry_list[i]->draw();
	//}
	//delete my_geometry;
	//delete my_child;


	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		//assign all pixels red color 
		for (int j = 0; j < height; j++)
			for (int i = 0; i < width; i++) {
				pixels[(i + width*j) * 3 + 0] = 1.0f;
				pixels[(i + width*j) * 3 + 1] = 1.0f;
				pixels[(i + width*j) * 3 + 2] = 1.0f;
			}


		//drawThickerLine();
		//draw();
		initializeObject();
		//drawEmptySquare();
		//drawcircle(500, 150, 50, 1.0f, 0.0f, 0.0f);
		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);


		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		std::cout << xpos << "   " << 480 - ypos << std::endl;
		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();

	delete[] pixels;
	//free(pixels);
	return 0;
}