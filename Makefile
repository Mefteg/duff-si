SOURCES =	$(wildcard *.cpp)
OBJECTS	=	$(SOURCES:.cpp=.o)
TARGET	=	duff
LIBS	= -lX11 -lGL -lGLU -lglut
CFLAGS	= -g
INCLUDES = glut

all: $(OBJECTS)
	g++ -o $(TARGET) $(OBJECTS) $(LIBS) -I $(INCLUDES)

%.o: %.cpp
	g++ -c $< -o $@ $(CFLAGS) -I $(INCLUDES)

x:	all
	./$(TARGET)

clean:
	rm -rf $(OBJECTS)

superclean : clean
	rm -rf $(TARGET)

