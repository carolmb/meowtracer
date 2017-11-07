all: main

CPP_FLAGS= -O3

define recipe
$(1).o: src/$(2)$(1).cpp src/$(2)$(1).h
	g++ -c $(CPP_FLAGS) src/$(2)$(1).cpp src/$(2)$(1).h
endef

main.o: main.cpp
	g++ -c $(CPP_FLAGS) main.cpp

LIGHTS = Light DirectionalLight PointLight SpotLight
$(foreach i,$(LIGHTS),$(eval $(call recipe,$(i),Light/)))

OBJS = Sphere
$(foreach i,$(OBJS),$(eval $(call recipe,$(i),Object/)))

CAMS = OrthogonalCamera PerspectiveCamera
$(foreach i,$(CAMS),$(eval $(call recipe,$(i),Camera/)))

RENDS = Renderer NormalRenderer MapRenderer DiffuseRenderer DefaultRenderer CelRenderer BlinnPhongRenderer
$(foreach i,$(RENDS),$(eval $(call recipe,$(i),Renderer/)))

SRC = Vec3 Vec4 Matrix4 InputData Image Scene
$(foreach i,$(SRC),$(eval $(call recipe,$(i),./)))

RECIPES = main.o $(foreach i, $(SRC) $(LIGHTS) $(OBJS) $(CAMS) $(RENDS), $(i).o)

main: $(RECIPES)
	g++ -o main $(RECIPES) -ljson_spirit
	rm -f src/*h.gch
	$(foreach i,Light Object Camera Renderer, rm -f src/$(i)/*.h.gch)

clean:
	rm -f *.o
	rm -f src/*h.gch
	$(foreach i,Light Object Camera Renderer, rm -f src/$(i)/*.h.gch)