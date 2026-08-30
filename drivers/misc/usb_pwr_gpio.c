/*
 * drivers/misc/usb_pwr_gpio.c
 *
 * Copyright (C) 2012-2016 Rockchip Co.,Ltd.
 * Author: Bin Yang <yangbin@rock-chips.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#include <linux/err.h>
#include <linux/gpio.h>
#include <linux/gpio/consumer.h>
#include <linux/kernel.h>
#include <linux/leds.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/property.h>
#include <linux/slab.h>
#include <linux/delay.h>

#include <linux/of_gpio.h>
#include <dt-bindings/gpio/gpio.h>

static struct class *usb_pwr_gpio_class;
struct usb_pwr_gpio {
	struct device *dev;
	struct device sys_dev;

	int gpio_usbhub1;
	int gpio_usbhub2;
	
	int gpio_led1;
	int gpio_led2;	
	int gpio_led3;	
};

static ssize_t usbhub1_show(struct device *sys_dev,
				 struct device_attribute *attr,
				 char *buf)
{
	struct usb_pwr_gpio *gpiod = container_of(sys_dev, struct usb_pwr_gpio,
						  sys_dev);

	return sprintf(buf, "%d\n", gpio_get_value(gpiod->gpio_usbhub1));
}

static ssize_t usbhub1_store(struct device *sys_dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	struct usb_pwr_gpio *gpiod = container_of(sys_dev, struct usb_pwr_gpio,
						  sys_dev);
	int val = 0;
	int ret = 0;

	ret = kstrtoint(buf, 0, &val);
	if (ret < 0)
		return ret;
	if (val)
		val = 1;
	
	if(val>0){
		gpio_set_value(gpiod->gpio_usbhub1, 1);
	}else{
		gpio_set_value(gpiod->gpio_usbhub1, 0);
	}
	return count;
}
static DEVICE_ATTR_RW(usbhub1);

static ssize_t usbhub2_show(struct device *sys_dev,
				 struct device_attribute *attr,
				 char *buf)
{
	struct usb_pwr_gpio *gpiod = container_of(sys_dev, struct usb_pwr_gpio,
						  sys_dev);

	return sprintf(buf, "%d\n", gpio_get_value(gpiod->gpio_usbhub2));
}

static ssize_t usbhub2_store(struct device *sys_dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	struct usb_pwr_gpio *gpiod = container_of(sys_dev, struct usb_pwr_gpio,
						  sys_dev);
	int val = 0;
	int ret = 0;

	ret = kstrtoint(buf, 0, &val);
	if (ret < 0)
		return ret;
	if (val)
		val = 1;
	
	if(val>0){
		gpio_set_value(gpiod->gpio_usbhub2, 1);
	}else{
		gpio_set_value(gpiod->gpio_usbhub2, 0);
	}
	return count;
}
static DEVICE_ATTR_RW(usbhub2);


static ssize_t led1_show(struct device *sys_dev,
				 struct device_attribute *attr,
				 char *buf)
{
	struct usb_pwr_gpio *gpiod = container_of(sys_dev, struct usb_pwr_gpio,
						  sys_dev);

	return sprintf(buf, "%d\n", gpio_get_value(gpiod->gpio_led1));
}

static ssize_t led1_store(struct device *sys_dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	struct usb_pwr_gpio *gpiod = container_of(sys_dev, struct usb_pwr_gpio,
						  sys_dev);
	int val = 0;
	int ret = 0;

	ret = kstrtoint(buf, 0, &val);
	if (ret < 0)
		return ret;
	if (val)
		val = 1;
	
	if(val>0){
		gpio_set_value(gpiod->gpio_led1, 1);
	}else{
		gpio_set_value(gpiod->gpio_led1, 0);
	}
	return count;
}
static DEVICE_ATTR_RW(led1);

static ssize_t led2_show(struct device *sys_dev,
				 struct device_attribute *attr,
				 char *buf)
{
	struct usb_pwr_gpio *gpiod = container_of(sys_dev, struct usb_pwr_gpio,
						  sys_dev);

	return sprintf(buf, "%d\n", gpio_get_value(gpiod->gpio_led2));
}

static ssize_t led2_store(struct device *sys_dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	struct usb_pwr_gpio *gpiod = container_of(sys_dev, struct usb_pwr_gpio,
						  sys_dev);
	int val = 0;
	int ret = 0;

	ret = kstrtoint(buf, 0, &val);
	if (ret < 0)
		return ret;
	if (val)
		val = 1;
	
	if(val>0){
		gpio_set_value(gpiod->gpio_led2, 1);
	}else{
		gpio_set_value(gpiod->gpio_led2, 0);
	}
	return count;
}
static DEVICE_ATTR_RW(led2);

static ssize_t led3_show(struct device *sys_dev,
				 struct device_attribute *attr,
				 char *buf)
{
	struct usb_pwr_gpio *gpiod = container_of(sys_dev, struct usb_pwr_gpio,
						  sys_dev);

	return sprintf(buf, "%d\n", gpio_get_value(gpiod->gpio_led3));
}

static ssize_t led3_store(struct device *sys_dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	struct usb_pwr_gpio *gpiod = container_of(sys_dev, struct usb_pwr_gpio,
						  sys_dev);
	int val = 0;
	int ret = 0;

	ret = kstrtoint(buf, 0, &val);
	if (ret < 0)
		return ret;
	if (val)
		val = 1;
	
	if(val>0){
		gpio_set_value(gpiod->gpio_led3, 1);
	}else{
		gpio_set_value(gpiod->gpio_led3, 0);
	}
	return count;
}
static DEVICE_ATTR_RW(led3);



static struct attribute *usb_pwr_gpio_attrs[] = {
	&dev_attr_usbhub1.attr,
	&dev_attr_usbhub2.attr,
	&dev_attr_led1.attr,	
	&dev_attr_led2.attr,	
	&dev_attr_led3.attr,		
	NULL,
};
ATTRIBUTE_GROUPS(usb_pwr_gpio);

static int usb_pwr_gpio_device_register(struct usb_pwr_gpio *gpiod)
{
	int ret;
	struct device *dev = &gpiod->sys_dev;
	const char *name = {"gpio"};

	dev->class = usb_pwr_gpio_class;
	dev_set_name(dev, "%s", name);
	dev_set_drvdata(dev, gpiod);
	ret = device_register(dev);

	return ret;
}


static int usb_pwr_gpio_probe(struct platform_device *pdev)
{
	
	struct usb_pwr_gpio *gpiod;
	struct device_node *node = pdev->dev.of_node;
	enum of_gpio_flags flags;
	int ret;
	int en_value;

	printk("usb_pwr_gpio_probe\n");
	usb_pwr_gpio_class = class_create(THIS_MODULE, "tyzc_gpio_ctl");
	if (IS_ERR(usb_pwr_gpio_class)) {
		pr_err("create uvc_detection class failed (%ld)\n",
		       PTR_ERR(usb_pwr_gpio_class));
		return PTR_ERR(usb_pwr_gpio_class);
	}
	usb_pwr_gpio_class->dev_groups = usb_pwr_gpio_groups;

	gpiod = devm_kzalloc(&pdev->dev, sizeof(*gpiod), GFP_KERNEL);
	if (!gpiod)
		return -ENOMEM;

	gpiod->dev = &pdev->dev;


	/***************************for usbhub power****************************/
	gpiod->gpio_led1 = of_get_named_gpio_flags(node, "led1,pin", 0, &flags);
	en_value = (flags == GPIO_ACTIVE_HIGH)? 1:0;
	if(!gpio_is_valid(gpiod->gpio_led1)){
		dev_err(&pdev->dev, "invalid gpiod->gpio_led1 %d\n", gpiod->gpio_led1);
	}
	ret = devm_gpio_request(&pdev->dev, gpiod->gpio_led1, "led1-gpio");
	if (ret) {
		dev_err(&pdev->dev,
			"failed to request gpiod->gpio_led1 %d for otg_drv\n",
			gpiod->gpio_led1);
		return -EINVAL;
	}
	
	gpio_direction_output(gpiod->gpio_led1, 0);

	/***************************for usbhub power****************************/
	gpiod->gpio_led2 = of_get_named_gpio_flags(node, "led2,pin", 0, &flags);
	en_value = (flags == GPIO_ACTIVE_HIGH)? 1:0;
	if(!gpio_is_valid(gpiod->gpio_led2)){
		dev_err(&pdev->dev, "invalid gpiod->gpio_led2 %d\n", gpiod->gpio_led2);
	}

	ret = devm_gpio_request(&pdev->dev, gpiod->gpio_led2, "led2-gpio");
	if (ret) {
		dev_err(&pdev->dev,
			"failed to request gpiod->gpio_led2 %d for otg_drv\n",
			gpiod->gpio_led2);
		return -EINVAL;
	}	
	gpio_direction_output(gpiod->gpio_led2, 0);

	/***************************for usbhub power****************************/
	gpiod->gpio_led3 = of_get_named_gpio_flags(node, "led3,pin", 0, &flags);
	en_value = (flags == GPIO_ACTIVE_HIGH)? 1:0;
	if(!gpio_is_valid(gpiod->gpio_led3)){
		dev_err(&pdev->dev, "invalid gpiod->gpio_led3 %d\n", gpiod->gpio_led3);
	}

	ret = devm_gpio_request(&pdev->dev, gpiod->gpio_led3, "led3-gpio");
	if (ret) {
		dev_err(&pdev->dev,
			"failed to request gpiod->gpio_led3 %d for otg_drv\n",
			gpiod->gpio_led3);
		return -EINVAL;
	}
	
	gpio_direction_output(gpiod->gpio_led3, 0);

	/***************************for usbhub power****************************/
	gpiod->gpio_usbhub1 = of_get_named_gpio_flags(node, "usbhub1,pin", 0, &flags);
	en_value = (flags == GPIO_ACTIVE_HIGH)? 1:0;
	if(!gpio_is_valid(gpiod->gpio_usbhub1)){
		dev_err(&pdev->dev, "invalid gpiod->gpio_usbhub1 %d\n", gpiod->gpio_usbhub1);
	}

	ret = devm_gpio_request(&pdev->dev, gpiod->gpio_usbhub1, "usbhub-gpio");
	if (ret) {
		dev_err(&pdev->dev,
			"failed to request gpiod->gpio_usbhub1 %d for otg_drv\n",
			gpiod->gpio_usbhub1);
		return -EINVAL;
	}
	
	gpio_direction_output(gpiod->gpio_usbhub1, 0);
	msleep(300);
	gpio_direction_output(gpiod->gpio_usbhub1, 1); 	
	
	ret = usb_pwr_gpio_device_register(gpiod);
	if (ret < 0) {
		dev_err(gpiod->dev, "usb_pwr_gpio device register fail\n");
		return ret;
	}

	dev_info(gpiod->dev, "usbhub success\n");

	return 0;
}

static const struct of_device_id usb_pwr_gpio_match[] = {
	{ .compatible = "tyzc-usbhub" },
	{ /* Sentinel */ }
};

static int usb_pwr_gpio_remove(struct platform_device *pdev)
{
	//if (!IS_ERR(usb_pwr_gpio_class))
	//	class_destroy(usb_pwr_gpio_class);

	return 0;
}

static struct platform_driver usb_pwr_gpio_driver = {
	.probe = usb_pwr_gpio_probe,
	.remove = usb_pwr_gpio_remove,
	.driver = {
		.name = "usb_pwr_gpio",
		.owner = THIS_MODULE,
		.of_match_table	= usb_pwr_gpio_match,
	},
};

module_platform_driver(usb_pwr_gpio_driver);

MODULE_ALIAS("platform:usb_pwr_gpio");
MODULE_AUTHOR("Bin Yang <yangbin@rock-chips.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("GPIO LED driver");
