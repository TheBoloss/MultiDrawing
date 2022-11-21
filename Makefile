APP_NAME := app

all: compile link

run: compile link
	./$(APP_NAME) $(ARGS)

compile:
ifndef PUBLISH
	g++ -c src/*.cpp -Iinclude
else
# Static:
	g++ -c src/*.cpp -Iinclude -DSFML_STATIC
endif

link:
# -mwindows to hide console
ifndef PUBLISH
	g++ *.o -o ./$(APP_NAME) -L lib -lsfml-graphics -lsfml-window -lsfml-system
else
# Static:
	g++ *.o -o ./$(APP_NAME) -L lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lgdi32 -lwinmm -mwindows -static
endif

ifeq ($(OS),Windows_NT)
clean:
	del *.o
	del $(APP_NAME).exe
else
clean:
	rm *.o
	rm $(APP_NAME)
endif