# In case the platform does NOT support this type of sensors
ccflags-y += -I$(srctree)/drivers/misc/mediatek/hwmon/include

ifeq ($(CONFIG_CUSTOM_KERNEL_ACCELEROMETER_MODULE),y)
obj-y   +=  accel_module.o accel_factory.o
else
obj-y   +=  accel.o accel_factory.o
endif

obj-$(CONFIG_MTK_LSM6DS0A)   +=  lsm6ds0/
