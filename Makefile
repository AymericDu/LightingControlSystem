MBED_PATH=$(shell mount | grep MBED | cut -d\  -f3)

compile:
	rm -rf ~/cross-compiler/smews/apps/lib/
	cp -R lib/ ~/cross-compiler/smews/apps/
	rm -rf ~/cross-compiler/smews/apps/light/
	cp -R light/ ~/cross-compiler/smews/apps/
	rm -rf ~/cross-compiler/smews/apps/light_sensor/
	cp -R light_sensor/ ~/cross-compiler/smews/apps/
	rm -rf ~/cross-compiler/smews/apps/luminosity/
	cp -R luminosity/ ~/cross-compiler/smews/apps/
	rm -rf ~/cross-compiler/smews/apps/lighting_control_system/
	cp -R lighting_control_system/ ~/cross-compiler/smews/apps/
	cd ~/cross-compiler/smews/; scons target=mbed_ethernet ipaddr=192.168.0.4 apps=:light,:light_sensor,:luminosity,:lighting_control_system,lib

program: compile
	rm $(MBED_PATH)/*.bin
	cp ~/cross-compiler/smews/bin/mbed_ethernet/smews.bin $(MBED_PATH) && sync
