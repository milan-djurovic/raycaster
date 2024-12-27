#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#define PI 3.14159265359 
#define P2 PI/2
#define P3 3*P2
#define DR 0.0174533

typedef struct {
	int w, a, s, d;
} ButtonKeys; ButtonKeys Keys;
float px, py, pdx, pdy, pa;

void drawPlayer() {
	glColor3f(1,0,1);
	glPointSize(8);
	glBegin(GL_POINTS);
	glVertex2i(px,py);
	glEnd();

	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2i(px, py);
	glVertex2i(px + pdx*5, py + pdy*5);
	glEnd();
}
int All_Textures[] = {
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0
};
int mapX = 16, mapY = 16, mapS = 32;
int map[] =
{
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1,
	1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1,
	1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1,
	1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
	1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1,
	1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

void drawMap2D() {
	int x, y, xo, yo;
	for (y = 0; y < mapY; y++) {
		for (x = 0; x < mapX; x++) {
			if (map[y*mapX+x] == 1)
				glColor3f(1, 1, 1);
			else
				glColor3f(0, 0, 0);
			xo = x * mapS;
			yo = y * mapS;
			glBegin(GL_QUADS);
			glVertex2i(xo + 1, yo + 1);
			glVertex2i(xo + 1, yo + mapS - 1);
			glVertex2i(xo + mapS - 1, yo + mapS - 1);
			glVertex2i(xo + mapS - 1, yo + 1);
			glEnd();
		}
	}
}

float dist(float ax, float ay, float bx, float by) {
	return sqrt ((bx - ax) * (bx - ax) + (by - ay) * (by - ay));
}

void drawRays2d() {
	float r;
	int mx, my, mp, dof;
	float rx, ry, ra, xo, yo, disT;
	
	ra = pa-DR*43; if (ra < 0) {ra += 2*PI;} if (ra > 2*PI) {ra -= 2*PI;}
	for (r = 0; r < 86; r += 0.5) {
		dof = 0; 
		float disH = 1000000, hx = px, hy = py;
		float aTan = -1 / tan(ra);
		if (ra > PI) {
			ry = (((int)py >> 5) << 5) - 0.0001;
			rx = (py-ry)*aTan+px;
			yo=-32;
			xo=-yo*aTan;
		}
		if (ra < PI) {
			ry = (((int)py >> 5) << 5) + 32;
			rx = (py-ry)*aTan+px;
			yo=32;
			xo=-yo*aTan;
		}
		if (ra == 0 || pa == PI) {
			rx = px;
			ry = py;
			dof = 16;
		}
		while (dof < 16) {
			mx = (int)(rx)>>5;
			my = (int)(ry)>>5;
			mp = my * mapX + mx;
			if (mp > 0 && mp < mapX*mapY && map[mp] == 1) {
				dof = 16;
				hx = rx;
				hy = ry;
				disH = dist(px, py, hx, hy);
			} else {
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}

		dof = 0; 
		float disV = 1000000, vx = px, vy = py;
		float nTan = -tan(ra);
		if (ra > P2 && ra < P3) {
			rx = (((int)px >> 5) << 5) - 0.0001;
			ry = (px-rx)*nTan+py;
			xo=-32;
			yo=-xo*nTan;
		}
		if (ra < P2 || ra > P3) {
			rx = (((int)px >> 5) << 5) + 32;
			ry = (px-rx)*nTan+py;
			xo=32;
			yo=-xo*nTan;
		}
		if (ra == 0 || pa == PI) {
			rx = px;
			ry = py;
			dof = 16;
		}
		while (dof < 16) {
			mx = (int)(rx)>>5;
			my = (int)(ry)>>5;
			mp = my * mapX + mx;
			if (mp > 0 && mp < mapX*mapY && map[mp] == 1) {
				dof = 16;
				vx = rx;
				vy = ry;
				disV = dist(px, py, vx, vy);
			} else {
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		float shade = 1;
		rx = hx; ry = hy; disT= disH; glColor3f(0.9,0,0);
		if (disV < disH) {rx = vx; ry = vy; disT = disV; glColor3f(0.7, 0, 0); shade = 0.5;}
		// glLineWidth(1);
		// glBegin(GL_LINES);
		// glVertex2i(px, py);
		// glVertex2i(rx, ry);
		// glEnd();

		float ca = pa - ra; if (ca < 0) { ca += 2*PI; } if (ca > 2*PI) {ca-=2*PI;}
		disT *= cos(ca);
		float lineH = (mapS*512)/disT;
		float ty_step = 32.0 / (float) lineH;
		float ty_off = 0;
		if(lineH > 512) {ty_off=(lineH-512)/2.0; lineH = 512;}
		float lineO = 256 - lineH / 2;

		int y;
		float ty = ty_off * ty_step;
		float tx;
		if (shade == 1) {
			tx = (int) (rx) % 32; if (ra > 180) {tx = 31 - tx;}
		} else {
			tx = (int) (ry) % 32; if (ra > 90 && ra < 270) {tx = 31 - tx;}
		}
		for (y = 0; y < lineH; y++) {
			float c = All_Textures[(int) ty*32 + (int) (tx)] * shade;
			glColor3f(c / 2.0, c / 10.0, c / 9.0);
			glPointSize(12);
			glBegin(GL_POINTS);
			glVertex2i(r*12, y + lineO);
			glEnd();
			ty += ty_step;
		}

		for (y = lineO + lineH; y < 512; y++) {
			float dy = y - (512 / 2.0);
			float raFix = pa - ra; if (raFix < 0) {raFix += 2*PI;} if (raFix > 2 * PI) {raFix -= 2*PI;}
			raFix = cos(raFix);
			tx = px / 2 + cos(ra) * 256 * 32 / dy / raFix;
			ty = py / 2 - sin(ra) * 256 * 32 / dy / raFix;
			float c = All_Textures[((int)(ty)&31)*32 + ((int)(tx)&31)] * 0.7;
			glColor3f(c / 9.0, c / 10.0, c / 9.0);
			glPointSize(12);
			glBegin(GL_POINTS);
			glVertex2i(r*12, y);
			glEnd();

			c = All_Textures[((int)(ty)&31)*32 + ((int)(tx)&31)] * 0.7;
			glColor3f(c / 9.0, c / 12.0, c / 1.5);
			glPointSize(12);
			glBegin(GL_POINTS);
			glVertex2i(r*12, 512 - y);
			glEnd();
		}
		ra+=DR/2; if (ra < 0) {ra += 2*PI;} if (ra > 2*PI) {ra -= 2*PI;}
	}
}

void display() {
	if (Keys.a==1) {
		pa -= 0.05;
		if (pa < 0)
			pa += 2*PI;
		pdx = cos(pa) * 3;
		pdy = sin(pa) * 3;
	}
	if (Keys.d==1) {
		pa += 0.1;
		if (pa > 2*PI)
			pa -= 2*PI;
		pdx = cos(pa) * 3;
		pdy = sin(pa) * 3;
	}
	int xo = 0; if (pdx<0) {xo=-10;} else {xo=10;}
	int yo = 0; if (pdy<0) {yo=-10;} else {yo=10;}
	int ipx = px/32, ipx_add_xo = (px+xo)/32, ipx_sub_xo = (px-xo)/32;
	int ipy = py/32, ipy_add_yo = (py+yo)/32, ipy_sub_yo = (py-yo)/32;
	if (Keys.w==1) {
		if (map[ipy * mapX + ipx_add_xo] == 0) px += pdx;
		if (map[ipy_add_yo * mapX + ipx] == 0) py += pdy;
	}
	if (Keys.s==1) {
		if (map[ipy * mapX + ipx_sub_xo] == 0) px -= pdx;
		if (map[ipy_sub_yo * mapX + ipx] == 0) py -= pdy;
	}
	glutPostRedisplay();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// drawMap2D();
	// drawPlayer();
	drawRays2d();
	glutSwapBuffers();
}

void resize (int w, int h) {
	glutReshapeWindow(1024, 512);
}

void ButtonDown(unsigned char key, int x, int y) {
	if (key == 'a') Keys.a=1;
	if (key == 'd') Keys.d=1;
	if (key == 'w') Keys.w=1;
	if (key == 's') Keys.s=1;
	glutPostRedisplay();
}

void ButtonUp(unsigned char key, int x, int y) {
	if (key == 'a') Keys.a=0;
	if (key == 'd') Keys.d=0;
	if (key == 'w') Keys.w=0;
	if (key == 's') Keys.s=0;
	glutPostRedisplay();
}

void init() {
	glClearColor(0.3, 0.3, 0.3, 0);
	gluOrtho2D(0, 1024, 512, 0);
	px = 300; py = 300; pa = 0;
	pdx = cos(pa) * 5;
	pdy = sin(pa) * 5;	
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1024, 512);
	glutCreateWindow("Game");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(ButtonDown);
	glutKeyboardUpFunc(ButtonUp);
	glutMainLoop();
}
