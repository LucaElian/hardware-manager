CXX      = g++
CXXFLAGS = -g -Wall -Wextra -Wpedantic -Wshadow -Wconversion -std=c++17 \
        -MMD -MP \
        -Iinclude -Iinclude/models -Iinclude/ui -Iinclude/managers -Itest

BUILDDIR = build/Debug
TARGET   = $(BUILDDIR)/gestorHardware.exe

SRCS = \
    main.cpp \
    utilidades.cpp \
    src/models/clsCliente.cpp \
    src/models/clsDetalleVenta.cpp \
    src/models/clsFecha.cpp \
    src/models/clsProducto.cpp \
    src/models/clsVendedor.cpp \
    src/models/clsVenta.cpp \
    src/ui/artworks.cpp \
    src/ui/menuCliente.cpp \
    src/ui/menuGen.cpp \
    src/ui/menuProducto.cpp \
    src/ui/menuReports.cpp \
    src/ui/menuVendedor.cpp \
    src/ui/menuVenta.cpp

OBJS = $(SRCS:%.cpp=$(BUILDDIR)/%.o)
DEPS = $(OBJS:.o=.d)

all: $(TARGET)

$(BUILDDIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -rf build

-include $(DEPS)
