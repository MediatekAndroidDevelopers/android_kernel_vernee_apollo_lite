# In case the platform does NOT support this type of sensors
ccflags-y += -I$(srctree)/drivers/misc/mediatek/hwmon/include
ifeq ($(CONFIG_CUSTOM_KERNEL_GYROSCOPE_MODULE),y)
obj-y   +=  gyroscope_module.o gyro_factory.o
else
obj-y   +=  gyroscope.o gyro_factory.o
endif

obj-$(CONFIG_MTK_LSM6DS0G)   +=  lsm6ds0gy/
