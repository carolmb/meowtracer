all: main

CPP_FLAGS= -g -std=c++11

define recipe
bin/$(1).o: src/$(2)$(1).cpp src/$(2)$(1).h
	g++ -c $(CPP_FLAGS) src/$(2)$(1).cpp -o bin/$(1).o
endef

bin/main.o: main.cpp
	g++ -c $(CPP_FLAGS) main.cpp -o bin/main.o

LIGHTS = Light DirectionalLight PointLight SpotLight AreaLight
$(foreach i,$(LIGHTS),$(eval $(call recipe,$(i),Light/)))

OBJS = Material Sphere Triangle
$(foreach i,$(OBJS),$(eval $(call recipe,$(i),Object/)))

CAMS = OrthogonalCamera PerspectiveCamera
$(foreach i,$(CAMS),$(eval $(call recipe,$(i),Camera/)))

RENDS = RendererUtil Renderer NormalRenderer MapRenderer DiffuseRenderer DielectricRenderer CelRenderer BlinnPhongRenderer
$(foreach i,$(RENDS),$(eval $(call recipe,$(i),Renderer/)))

MATH = Vec3 Vec4 Matrix4 Perlin
$(foreach i,$(MATH),$(eval $(call recipe,$(i),Math/)))

PARSER = InputData MathParser SceneParser ObjectParser
$(foreach i,$(PARSER),$(eval $(call recipe,$(i),Parser/)))

SRC = Image Scene
$(foreach i,$(SRC),$(eval $(call recipe,$(i),./)))

RECIPES = bin/main.o $(foreach i, $(MATH) $(SRC) $(PARSER) $(LIGHTS) $(OBJS) $(CAMS) $(RENDS), bin/$(i).o)

FOLDERS = Math Parser Light Object Camera Renderer

main: $(RECIPES)
	g++ -o main $(RECIPES) -ljson_spirit
	rm -f src/*h.gch
	$(foreach i,$(FOLDERS), rm -f src/$(i)/*.h.gch)

clean:
	rm -f bin/*.o
	rm -f src/*h.gch
	$(foreach i,$(FOLDERS), rm -f src/$(i)/*.h.gch)