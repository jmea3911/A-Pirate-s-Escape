# Nombre del ejecutable
TARGET = juego

# Directorios
SRC_DIR = Src
OBJ_DIR = Src/output

# Compilador y ensamblador
CXX = g++
NASM = nasm

# Flags de compilación 100% nativos
CXXFLAGS = -Wall -I$(SRC_DIR) `pkg-config --cflags sdl3`

# Forzar ruta de librerías en tiempo de compilación y ejecución
LDFLAGS = -L/usr/local/lib -Wl,-rpath=/usr/local/lib `pkg-config --libs sdl3` -lSDL3_image

# Archivos fuente y objeto
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

# Regla por defecto: compilar
all: clean $(TARGET)

# Compilar el ejecutable
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Compilar cada .cpp a .o en output/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para ejecutar después de compilar
run: all
	./$(TARGET)

# Limpiar archivos intermedios y ejecutable
clean:
	rm -f $(OBJ) $(TARGET)
