#include "SongVisualizer.h"

int main(int n, char **args) {
	wchar_t h = wchar_t("Hello world");
	Song *s = new Song(&h);
	delete s;
}