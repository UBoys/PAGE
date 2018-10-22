import platform

os = platform.system()

if os == 'Windows' :
	print("On windows, running bat script")
	from subprocess import Popen
	Popen('windows\disableVulkanValidationLayers.bat')
	print("If running from a cmd window you may need to close it and open a new cmd window for changes to take effect")
elif os == 'Linux' :
	print("On Linux, TODO: not yet implemented")
elif os == 'Darwin' :
	print("On Mac, TODO: not yet implemented")