TARGET = calculadora_boleana

CXX = g++

CXXFLAGS = -std=c++11 -Wall -Wextra

SOURCES = arvore_operacoes.cpp main.cpp vars_map_table.cpp funcoes_memoria.cpp no_tabela_verdade.cpp get_results.cpp validations.cpp

OBJECTS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

all: $(TARGET)

.PHONY: clean all

