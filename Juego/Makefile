# Nombre del ejecutable
TARGET = juego

# Directorios
SRC_DIR = Src
OBJ_DIR = Src/output
ASM_DIR = Asm

# Compilador y ensamblador
CXX = g++
NASM = nasm

# Flags de compilación
CXXFLAGS = -Wall -I$(SRC_DIR) `pkg-config --cflags sdl3`

# Librerías
LDFLAGS = -L/usr/local/lib -Wl,-rpath=/usr/local/lib `pkg-config --libs sdl3` -lSDL3_image -lSDL3_mixer -lc

# Archivos fuente y objeto
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

# Archivos NASM
ASM = $(ASM_DIR)/moverObjeto.asm $(ASM_DIR)/moverBarco.asm
ASM_OBJ = $(ASM:.asm=.o)

# Regla por defecto: compilar todo
all: clean $(TARGET)

# Compilar el ejecutable
$(TARGET): $(OBJ) $(ASM_OBJ)
	$(CXX) $(OBJ) $(ASM_OBJ) -o $(TARGET) $(LDFLAGS) -no-pie

# Compilar cada .cpp a .o en output/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilar NASM a objeto
$(ASM_DIR)/%.o: $(ASM_DIR)/%.asm
	$(NASM) -f elf64 -o $@ $<

# Regla para ejecutar después de compilar
run: all
	./$(TARGET)

# Limpiar archivos intermedios y ejecutable
clean:
	rm -f $(OBJ) $(ASM_OBJ) $(TARGET)
