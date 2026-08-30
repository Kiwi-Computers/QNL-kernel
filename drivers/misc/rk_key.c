/*
 * drivers/misc/rk_key.c
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

#include <linux/of_gpio.h>
#include <dt-bindings/gpio/gpio.h>


#define VERITY_COMMANDLINE_PARAM_LENGTH 20

#define SN_ID 1
#define LAN_MAC_ID 3
#define CUSTOMIZE1_ID 12
//struct wake_lock wlock;
static struct class *rk_key_class;

static char serialno[VERITY_COMMANDLINE_PARAM_LENGTH];

struct rk_key {
	struct device *dev;
	struct device sys_dev;
};

extern int rk_vendor_write(u32 id, void *pbuf, u32 size);
extern int rk_vendor_read(u32 id, void *pbuf, u32 size);

unsigned char char2num(unsigned char ch)
{   
    switch(ch){
        case 'a':
        case 'A':
            return 10;
            break;
        case 'b':
        case 'B':
            return 11;
            break;
        case 'c':
        case 'C':
            return 12;
            break;
        case 'd':
        case 'D':
            return 13;
            break;
        case 'e':
        case 'E':
            return 14;
            break;
        case 'f':
        case 'F':
            return 15;
            break;
        default:
            return 0;
    }
}

void str2byte(const char *str, unsigned char *byte)
{
    int i=0, j=0;
    unsigned char num, n;
    unsigned char temp[20] = {0};

    for(i=0; i<17; i++){
        if(str[i] == ':'){
            continue;
        }else{
            temp[j] = str[i];
            j++;
        }
    }
    temp[j]='\0';
    i=0;
    while(*(temp+i)!='\0')
    {
        if(*(temp+i)>='0' && *(temp+i) <= '9'){
            if(i%2 == 0){
                num = (*(temp+i)-'0') * 16;
            }else{
                num = num + (*(temp+i)-'0');
            }
            i++;
        }else if((*(temp+i)>='a' && *(temp+i) <= 'f') || (*(temp+i)>='A' && *(temp+i) <= 'F')){
            n = char2num(*(temp+i));
            if(n == 0){
                memset(byte, 0, 6);
                break;
            }
            if(i%2 == 0){
                num = n * 16;
            }else{
                num = num + n;
            }
            i++;
        }else{
            memset(byte, 0, 6);
            break;
        }
        if(i%2 == 0){
            *byte++ = num;
        }

    }
}

static ssize_t dev_sn_show(struct device *sys_dev,
                                 struct device_attribute *attr,
                                 char *buf)
{       

        return sprintf(buf, "%s", serialno);
}


static int __init serialno_param(char *line)
{
        strlcpy(serialno, line, sizeof(serialno));
        return 1;
}

__setup("androidboot.serialno=", serialno_param);

static ssize_t dev_sn_store(struct device *sys_dev,
                                  struct device_attribute *attr,
                                  const char *buf, size_t count)
{
        return count;
}
static DEVICE_ATTR_RW(dev_sn);


static ssize_t customize1_show(struct device *sys_dev,
				 struct device_attribute *attr,
				 char *buf)
{

	char key_value[32] ;
	memset(key_value,0,32);
	rk_vendor_read(CUSTOMIZE1_ID,key_value,32);
	
	return sprintf(buf, "%s", key_value);
}

static ssize_t customize1_store(struct device *sys_dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	char key_value[32] ;
	memset(key_value,0,32);
	strcpy(key_value,buf);
	printk("----jkren---key_value==%s",key_value);
	
	rk_vendor_write(CUSTOMIZE1_ID,key_value,count);
	
	return count;
}

static DEVICE_ATTR_RW(customize1);

static ssize_t sn_number_show(struct device *sys_dev,
				 struct device_attribute *attr,
				 char *buf)
{
	char key_value[32] ;
	memset(key_value,0,32);
	rk_vendor_read(SN_ID,key_value,32);
	
	return sprintf(buf, "%s", key_value);
}

static ssize_t sn_number_store(struct device *sys_dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	char key_value[32] ;
	memset(key_value,0,32);
	strcpy(key_value,buf);
	printk("----jkren---key_value==%s",key_value);
	rk_vendor_write(SN_ID,key_value,count);
	
	return count;
}

static DEVICE_ATTR_RW(sn_number);

static ssize_t lan_mac_show(struct device *sys_dev,
				 struct device_attribute *attr,
				 char *buf)
{
	char temp_mac_buf[17];
	memset(temp_mac_buf,0,sizeof(temp_mac_buf));
	rk_vendor_read(LAN_MAC_ID,temp_mac_buf,sizeof(temp_mac_buf));
	
	return sprintf(buf, "%pM", temp_mac_buf);
}

static ssize_t lan_mac_store(struct device *sys_dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	unsigned char mac_addr[7] = {0};
	str2byte(buf, mac_addr);
	printk(KERN_ERR"[%s:%d]%02x:%02x:%02x:%02x:%02x:%02x\r\n",__func__,__LINE__,mac_addr[0],mac_addr[1],mac_addr[2],mac_addr[3],mac_addr[4],mac_addr[5]);
	rk_vendor_write(LAN_MAC_ID,mac_addr,count-1);
	
	return count;
}

static DEVICE_ATTR_RW(lan_mac);

static struct attribute *rk_key_attrs[] = {
	&dev_attr_dev_sn.attr,
	&dev_attr_sn_number.attr,
	&dev_attr_customize1.attr,
	&dev_attr_lan_mac.attr,
	NULL,
};
ATTRIBUTE_GROUPS(rk_key);




static int rk_key_device_register(struct rk_key *gpiod)
{
	int ret;
	struct device *dev = &gpiod->sys_dev;
	const char *name = {"key_value"};

	dev->class = rk_key_class;
	dev_set_name(dev, "%s", name);
	dev_set_drvdata(dev, gpiod);
	ret = device_register(dev);

	return ret;
}

static int rk_key_probe(struct platform_device *pdev)
{
	struct rk_key *gpiod;
	int ret = 0;

	printk("---jkren-1-rk_key_probe\n");
	rk_key_class = class_create(THIS_MODULE, "rk_key");
	if (IS_ERR(rk_key_class)) {
		pr_err("create uvc_detection class failed (%ld)\n",
		       PTR_ERR(rk_key_class));
		return PTR_ERR(rk_key_class);
	}
	rk_key_class->dev_groups = rk_key_groups;
	
	printk("---jkren-2-rk_key_probe\n");
	gpiod = devm_kzalloc(&pdev->dev, sizeof(*gpiod), GFP_KERNEL);
	if (!gpiod)
		return -ENOMEM;

	gpiod->dev = &pdev->dev;
	
	printk("---jkren-3-rk_key_probe\n");
	ret = rk_key_device_register(gpiod);
	if (ret < 0) {
		dev_err(gpiod->dev, "rk_key device register fail\n");
		return ret;
	}

	dev_info(gpiod->dev, "rk_key_probe success\n");
 	//wake_lock_init(&wlock, WAKE_LOCK_SUSPEND, "wlock name");
	//wake_lock(&wlock);
	printk("rk_key_probe end\n");
	return 0;
}

static const struct of_device_id rk_key_match[] = {
	{ .compatible = "usb-pwr-gpio" },
	{ /* Sentinel */ }
};

static int rk_key_remove(struct platform_device *pdev)
{
	if (!IS_ERR(rk_key_class))
		class_destroy(rk_key_class);

	return 0;
}

static struct platform_driver rk_key_driver = {
	.probe = rk_key_probe,
	.remove = rk_key_remove,
	.driver = {
		.name = "rk_key",
		.owner = THIS_MODULE,
		.of_match_table	= rk_key_match,
	},
};

module_platform_driver(rk_key_driver);

MODULE_ALIAS("platform:rk_key");
MODULE_AUTHOR("Bin Yang <yangbin@rock-chips.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("usb id and fp power gpio driver");
