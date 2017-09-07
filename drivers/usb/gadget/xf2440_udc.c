/*
 * author:zhangqiang	
 * date:2017.09.06
 * email:jonnezhang@126.com
 */


#if 1

#include <usb.h>
#include <linux/usb/gadget.h>


#include <asm/io.h>





/***************************reg define start********************************/
#define XF2440_GPIO_GPGCON					(0x56000060)
#define XF2440_GPIO_GPGDAT					(0x56000064)
#define XF2440_GPIO_GPGUP					(0x56000068)


#define XF2440_UDC_BASE			0x52000000

#define XF2440_UDC_PWR_REG					(XF2440_UDC_BASE + 0X144)
#define XF2440_UDC_EP_INT_REG				(XF2440_UDC_BASE + 0X148)
#define XF2440_UDC_USB_INT_REG				(XF2440_UDC_BASE + 0X158)

#define XF2440_UDC_EP_INT_EN_REG				(XF2440_UDC_BASE + 0X15C)
#define XF2440_UDC_USB_INT_EN_REG				(XF2440_UDC_BASE + 0X16C)









#define XF2440_UDC_INDEX_REG				(XF2440_UDC_BASE + 0X178)

#define XF2440_UDC_MAXP_REG					(XF2440_UDC_BASE + 0X180)
#define XF2440_UDC_EP0_CSR_IN_CSR1_REG		(XF2440_UDC_BASE + 0X184)
#define XF2440_UDC_IN_CSR2_REG				(XF2440_UDC_BASE + 0X188)
#define XF2440_UDC_OUT_CSR1_REG				(XF2440_UDC_BASE + 0X190)
#define XF2440_UDC_OUT_CSR2_REG				(XF2440_UDC_BASE + 0X194)















/* ENDPOINT0 CSR (Control Status Register) : Mapped to IN CSR1 */
#define EP0_OUT_PKT_READY        0x01  /* USB sets, MCU clears by setting SERVICED_OUT_PKT_RDY */
#define EP0_IN_PKT_READY         0x02  /* MCU sets, USB clears after sending FIFO */
#define EP0_SENT_STALL           0x04  /* USB sets */       
#define EP0_DATA_END             0x08  /* MCU sets */
#define EP0_SETUP_END            0x10  /* USB sets, MCU clears by setting SERVICED_SETUP_END */
#define EP0_SEND_STALL           0x20  /* MCU sets */
#define EP0_SERVICED_OUT_PKT_RDY 0x40  /* MCU writes 1 to clear OUT_PKT_READY */
#define EP0_SERVICED_SETUP_END   0x80  /* MCU writes 1 to clear SETUP_END        */


//IN_CSR1
#define EPI_IN_PKT_READY         0x01  
#define EPI_UNDER_RUN		 0x04
#define EPI_FIFO_FLUSH		 0x08
#define EPI_SEND_STALL           0x10  
#define EPI_SENT_STALL           0x20  
#define EPI_CDT			 0x40	
#define EPI_WR_BITS              (EPI_FIFO_FLUSH|EPI_IN_PKT_READY|EPI_CDT) 

//IN_CSR2
#define EPI_IN_DMA_INT_MASK	(1<<4)
#define EPI_MODE_IN		(1<<5)
#define EPI_MODE_OUT		(0<<5)
#define EPI_ISO			(1<<6)
#define EPI_BULK		(0<<6)
#define EPI_AUTO_SET		(1<<7)

//OUT_CSR1
#define EPO_OUT_PKT_READY        0x01  
#define EPO_OVER_RUN		 0x04  
#define EPO_DATA_ERROR		 0x08  
#define EPO_FIFO_FLUSH		 0x10
#define EPO_SEND_STALL           0x20  
#define EPO_SENT_STALL           0x40
#define EPO_CDT			 0x80	
#define EPO_WR_BITS              (EPO_FIFO_FLUSH|EPO_SEND_STALL|EPO_CDT)


//OUT_CSR2
#define EPO_OUT_DMA_INT_MASK	(1<<5)
#define EPO_ISO		 	(1<<6)
#define EPO_BULK	 	(0<<6)
#define EPO_AUTO_CLR		(1<<7)


//EP_INT_REG / EP_INT_EN_REG
#define EP0_INT                	 0x01  // Endpoint 0, Control   
#define EP1_INT                  0x02  // Endpoint 1, (Bulk-In) 
#define EP2_INT                  0x04  // Endpoint 2 
#define EP3_INT			 0x08  // Endpoint 3, (Bulk-Out)   
#define EP4_INT			 0x10  // Endpoint 4

//USB_INT_REG / USB_INT_EN_REG
#define SUSPEND_INT            	 0x01  
#define RESUME_INT               0x02  
#define RESET_INT                0x04  


#define EP0_WR_BITS              0xc0 








/***************************reg define   end********************************/

/* MAXP Register */
#define FIFO_SIZE_0              0x00  /* 0x00 * 8 = 0  */
#define FIFO_SIZE_8              0x01  /* 0x01 * 8 = 8  */
#define FIFO_SIZE_16             0x02  /* 0x02 * 8 = 16 */
#define FIFO_SIZE_32             0x04  /* 0x04 * 8 = 32 */
#define FIFO_SIZE_64             0x08  /* 0x08 * 8 = 64 */

#define XF2440_MAX_ENDPOINTS	5



#define CLR_EP0_OUT_PKT_RDY() 		writeb(((ep0_csr & (~EP0_WR_BITS)) | EP0_SERVICED_OUT_PKT_RDY ), XF2440_UDC_EP0_CSR_IN_CSR1_REG)	 
#define CLR_EP0_OUTPKTRDY_DATAEND() 	writeb(((ep0_csr & (~EP0_WR_BITS)) | (EP0_SERVICED_OUT_PKT_RDY | EP0_DATA_END)), XF2440_UDC_EP0_CSR_IN_CSR1_REG)
#define SET_EP0_IN_PKT_RDY() 		writeb(((ep0_csr & (~EP0_WR_BITS)) | (EP0_IN_PKT_READY)), XF2440_UDC_EP0_CSR_IN_CSR1_REG)	 
#define SET_EP0_INPKTRDY_DATAEND() 	writeb(((ep0_csr & (~EP0_WR_BITS)) | (EP0_IN_PKT_READY|EP0_DATA_END)), XF2440_UDC_EP0_CSR_IN_CSR1_REG)			
#define CLR_EP0_SETUP_END()		writeb(((ep0_csr & (~EP0_WR_BITS)) | (EP0_SERVICED_SETUP_END)), XF2440_UDC_EP0_CSR_IN_CSR1_REG)			
#define CLR_EP0_SENT_STALL() 		writeb(((ep0_csr & (~EP0_WR_BITS)) & (~EP0_SENT_STALL)), XF2440_UDC_EP0_CSR_IN_CSR1_REG)			
#define FLUSH_EP0_FIFO() 		{ while (readb(&usbdevregs->OUT_FIFO_CNT1_REG)) { readb(&usbdevregs->fifo[0].EP_FIFO_REG);}}



struct xf2440_udc {
	struct usb_gadget gadget;
	struct usb_gadget_driver *driver;

	//struct s3c_plat_otg_data *pdata;

	//int ep0state;
	struct usb_ep ep[XF2440_MAX_ENDPOINTS];

	unsigned char usb_address;

	unsigned req_pending:1, req_std:1;
};


static struct xf2440_udc *the_controller;


static void xf2440_udc_reinit(struct xf2440_udc *dev)
{
// *** End point information ***
//   EP0: control
//   EP1: bulk in end point
//   EP2: not used
//   EP3: bulk out end point
//   EP4: not used
	//struct s3c24x0_usb_device * const usbdevregs	= s3c24x0_get_base_usb_device();   
 
	writeb(0x00, XF2440_UDC_PWR_REG);//writeb(PWR_REG_DEFAULT_VALUE, &usbdevregs->PWR_REG); //disable suspend mode
	
	writeb(0, XF2440_UDC_INDEX_REG);//writeb(0, &usbdevregs->INDEX_REG); 
	writeb(FIFO_SIZE_8, XF2440_UDC_MAXP_REG);//writeb(FIFO_SIZE_8, &usbdevregs->MAXP_REG); //EP0 max packit size = 8 
	writeb(EP0_SERVICED_OUT_PKT_RDY | EP0_SERVICED_SETUP_END, XF2440_UDC_EP0_CSR_IN_CSR1_REG);//writeb((EP0_SERVICED_OUT_PKT_RDY | EP0_SERVICED_SETUP_END), & usbdevregs->EP0_CSR_IN_CSR1_REG); //EP0:clear OUT_PKT_RDY & SETUP_END

	writeb(1, XF2440_UDC_INDEX_REG); //writeb(1, &usbdevregs->INDEX_REG);
	writeb(FIFO_SIZE_32, XF2440_UDC_MAXP_REG);//writeb(FIFO_SIZE_32, &usbdevregs->MAXP_REG); //EP1:max packit size = 32
	writeb(EPI_FIFO_FLUSH | EPI_CDT, XF2440_UDC_EP0_CSR_IN_CSR1_REG);//writeb((EPI_FIFO_FLUSH | EPI_CDT), &usbdevregs->EP0_CSR_IN_CSR1_REG); 
	writeb(EPI_MODE_IN | EPI_IN_DMA_INT_MASK | EPI_BULK, XF2440_UDC_IN_CSR2_REG);//writeb((EPI_MODE_IN | EPI_IN_DMA_INT_MASK | EPI_BULK), &usbdevregs->IN_CSR2_REG);  //IN mode, IN_DMA_INT=masked    
	writeb(EPO_CDT, XF2440_UDC_OUT_CSR1_REG);//writeb(EPO_CDT, &usbdevregs->OUT_CSR1_REG); 
	writeb(EPO_BULK | EPO_OUT_DMA_INT_MASK, XF2440_UDC_OUT_CSR2_REG);//writeb((EPO_BULK | EPO_OUT_DMA_INT_MASK), &usbdevregs->OUT_CSR2_REG); 

	writeb(2, XF2440_UDC_INDEX_REG);//writeb(2, &usbdevregs->INDEX_REG); 
	writeb(FIFO_SIZE_64, XF2440_UDC_MAXP_REG);//writeb(FIFO_SIZE_64, &usbdevregs->MAXP_REG); //EP2:max packit size = 64
	writeb(EPI_FIFO_FLUSH | EPI_CDT | EPI_BULK, XF2440_UDC_EP0_CSR_IN_CSR1_REG);//writeb((EPI_FIFO_FLUSH | EPI_CDT | EPI_BULK), &usbdevregs->EP0_CSR_IN_CSR1_REG); 
	writeb(EPI_MODE_IN | EPI_IN_DMA_INT_MASK, XF2440_UDC_IN_CSR2_REG);//writeb((EPI_MODE_IN | EPI_IN_DMA_INT_MASK), &usbdevregs->IN_CSR2_REG);  //IN mode, IN_DMA_INT=masked    
	writeb(EPO_CDT, XF2440_UDC_OUT_CSR1_REG);//writeb(EPO_CDT, &usbdevregs->OUT_CSR1_REG); 
	writeb(EPO_BULK | EPO_OUT_DMA_INT_MASK, XF2440_UDC_OUT_CSR2_REG);//writeb((EPO_BULK | EPO_OUT_DMA_INT_MASK), &usbdevregs->OUT_CSR2_REG); 

	writeb(3, XF2440_UDC_INDEX_REG);//writeb(3, &usbdevregs->INDEX_REG); 
	writeb(FIFO_SIZE_32, XF2440_UDC_MAXP_REG);//writeb(FIFO_SIZE_32, &usbdevregs->MAXP_REG); //EP3:max packit size = 32
	writeb(EPI_FIFO_FLUSH | EPI_CDT | EPI_BULK, XF2440_UDC_EP0_CSR_IN_CSR1_REG);//writeb((EPI_FIFO_FLUSH | EPI_CDT | EPI_BULK), &usbdevregs->EP0_CSR_IN_CSR1_REG); 	
	writeb(EPI_MODE_OUT | EPI_IN_DMA_INT_MASK, XF2440_UDC_IN_CSR2_REG);//writeb((EPI_MODE_OUT | EPI_IN_DMA_INT_MASK), &usbdevregs->IN_CSR2_REG); //OUT mode, IN_DMA_INT=masked    
	writeb(EPO_CDT, XF2440_UDC_OUT_CSR1_REG);//writeb(EPO_CDT, &usbdevregs->OUT_CSR1_REG); 
	writeb(EPO_BULK | EPO_OUT_DMA_INT_MASK, XF2440_UDC_OUT_CSR2_REG);//writeb((EPO_BULK | EPO_OUT_DMA_INT_MASK), &usbdevregs->OUT_CSR2_REG); 

	writeb(4, XF2440_UDC_INDEX_REG);//writeb(4, &usbdevregs->INDEX_REG); 
	writeb(FIFO_SIZE_64, XF2440_UDC_MAXP_REG);//writeb(FIFO_SIZE_64, &usbdevregs->MAXP_REG); //EP4:max packit size = 64
	writeb(EPI_FIFO_FLUSH | EPI_CDT | EPI_BULK, XF2440_UDC_EP0_CSR_IN_CSR1_REG);//writeb((EPI_FIFO_FLUSH | EPI_CDT | EPI_BULK), &usbdevregs->EP0_CSR_IN_CSR1_REG); 
	writeb(EPI_MODE_OUT | EPI_IN_DMA_INT_MASK, XF2440_UDC_IN_CSR2_REG);//writeb((EPI_MODE_OUT | EPI_IN_DMA_INT_MASK), &usbdevregs->IN_CSR2_REG); //OUT mode, IN_DMA_INT=masked    
	writeb(EPO_CDT, XF2440_UDC_OUT_CSR1_REG);//writeb(EPO_CDT, &usbdevregs->OUT_CSR1_REG); 
	writeb(EPO_BULK | EPO_OUT_DMA_INT_MASK, XF2440_UDC_OUT_CSR2_REG);//writeb((EPO_BULK | EPO_OUT_DMA_INT_MASK), &usbdevregs->OUT_CSR2_REG); 
    
	writeb(EP0_INT | EP1_INT | EP2_INT | EP3_INT | EP4_INT, XF2440_UDC_EP_INT_REG);//writeb((EP0_INT | EP1_INT | EP2_INT | EP3_INT | EP4_INT), &usbdevregs->EP_INT_REG); 
	writeb(RESET_INT | SUSPEND_INT | RESUME_INT, XF2440_UDC_USB_INT_REG);//writeb((RESET_INT | SUSPEND_INT | RESUME_INT), &usbdevregs->USB_INT_REG); 
    	
	writeb(EP0_INT | EP1_INT | EP3_INT, XF2440_UDC_EP_INT_EN_REG);//writeb((EP0_INT | EP1_INT | EP3_INT), &usbdevregs->EP_INT_EN_REG); 
	writeb(RESET_INT, XF2440_UDC_USB_INT_EN_REG);//writeb(RESET_INT, &usbdevregs->USB_INT_EN_REG); 

	printf("XF2440_UDC_OUT_CSR2_REG:0x%02x \n", readb(XF2440_UDC_OUT_CSR2_REG));
	printf("XF2440_UDC_EP_INT_EN_REG:0x%02x \n", readb(XF2440_UDC_EP_INT_EN_REG));






	
    //    ep0State = EP0_STATE_INIT;
    
}

/*
void RdPktEp0(U8 *buf,int num)
{
    int i;
	struct s3c24x0_usb_device * const usbdevregs	= s3c24x0_get_base_usb_device();   
 	
    for(i=0;i<num;i++)
    {
	 buf[i] = readb(&usbdevregs->fifo[0].EP_FIFO_REG);
    }
}
*/



static int xf2440_udc_enble(struct xf2440_udc *dev)
{
	xf2440_udc_reinit(dev);
	
	return 0;
}

static void Ep0Handler()
{
	unsigned char ep0_csr;

	writeb(0, XF2440_UDC_INDEX_REG);	
	ep0_csr = readb(XF2440_UDC_EP0_CSR_IN_CSR1_REG);

	 if(ep0_csr & EP0_SETUP_END)
    {   
    	 // Host may end GET_DESCRIPTOR operation without completing the IN data stage.
    	 // If host does that, SETUP_END bit will be set.
    	 // OUT_PKT_RDY has to be also cleared because status stage sets OUT_PKT_RDY to 1.
//   	DbgPrintf("[SETUPEND]");
		CLR_EP0_SETUP_END();
		if(ep0_csr & EP0_OUT_PKT_READY) 
		{
		   // FLUSH_EP0_FIFO(); //(???)
		    	//I think this isn't needed because EP0 flush is done automatically.   
		    CLR_EP0_OUT_PKT_RDY();
		}
		
		//ep0State=EP0_STATE_INIT;
		return;
    }	

	 //I think that EP0_SENT_STALL will not be set to 1.
    if(ep0_csr & EP0_SENT_STALL)
    {   
  // 	DbgPrintf("[STALL]");
	   	CLR_EP0_SENT_STALL();
		if(ep0_csr & EP0_OUT_PKT_READY) 
		{
		    CLR_EP0_OUT_PKT_RDY();
		}
		
		//ep0State=EP0_STATE_INIT;
		return;
    }


	if((ep0_csr & EP0_OUT_PKT_READY)) // && (ep0State==EP0_STATE_INIT))
	{	
		//RdPktEp0((U8 *)&descSetup,EP0_PKT_SIZE);
	}
	
	
}

	

static int xf2440_udc_irq(void *dev)
{
    unsigned char usbdIntpnd,epIntpnd;
    unsigned char saveIndexReg;


	saveIndexReg = readb(XF2440_UDC_INDEX_REG);

    usbdIntpnd = readb(XF2440_UDC_USB_INT_REG);
    epIntpnd = readb(XF2440_UDC_EP_INT_REG);
  //  printf( "[INT:EP_I=%x,USBI=%x] \n",epIntpnd,usbdIntpnd );

    if(usbdIntpnd&SUSPEND_INT)
    {
		writeb(SUSPEND_INT, XF2440_UDC_USB_INT_REG);
    		printf( "<SUS]");
    }
    if(usbdIntpnd&RESUME_INT)
    {
		writeb(RESUME_INT, XF2440_UDC_USB_INT_REG);
	    	printf("<RSM]");
    }
    if(usbdIntpnd&RESET_INT)
    {
    	printf( "<RST] ReconfigUsbd");  
    	
    	xf2440_udc_reinit(dev);
		writeb(RESET_INT, XF2440_UDC_USB_INT_REG); //RESET_INT should be cleared after ResetUsbd().   	
    }

    if(epIntpnd&EP0_INT)
    {
    	printf( "<EP0_INT] ");
		writeb(EP0_INT, XF2440_UDC_EP_INT_REG);
    	Ep0Handler();
    }
    if(epIntpnd&EP1_INT)
    {
		writeb(EP1_INT, XF2440_UDC_EP_INT_REG);
//    	Ep1Handler();
    }

    if(epIntpnd&EP2_INT)
    {
		writeb(EP2_INT, XF2440_UDC_EP_INT_REG);
    //	printk("<2:TBD]\n");   //not implemented yet	
    	//Ep2Handler();
    }

    if(epIntpnd&EP3_INT)
    {
		writeb(EP3_INT, XF2440_UDC_EP_INT_REG);
    	//Ep3Handler();
    }

    if(epIntpnd&EP4_INT)
    {
		writeb(EP4_INT, XF2440_UDC_EP_INT_REG);
    }
	
	writeb(saveIndexReg, XF2440_UDC_INDEX_REG); 
	
}

static int	xf2440_udc_pullup (struct usb_gadget * gadget, int is_on)
{

	int val;

	val = readl(XF2440_GPIO_GPGCON);
	val &= ~(0x3<<24);
	val |= 1<<24;
	writel(val, XF2440_GPIO_GPGCON);		
	writel(0x0000efff, XF2440_GPIO_GPGUP);


	val = readl(XF2440_GPIO_GPGDAT);
	val |= 	(1 << 12);
	writel(val, XF2440_GPIO_GPGDAT);

	return 0;
}



/************************************hardware over************************************************/

struct usb_request * xf2440_ep_alloc_request(struct usb_ep *ep,
		gfp_t gfp_flags)
{
	struct usb_request *req;

	printf("XF2440: %s ================ \n", __func__);

	req = memalign(CONFIG_SYS_CACHELINE_SIZE, sizeof(struct usb_request));
	if (!req)
		return 0;

	memset(req, 0, sizeof(struct usb_request));

	return req;
}


static struct usb_gadget_ops xf2440_gadget_ops = {
	.pullup = xf2440_udc_pullup,
};

struct usb_ep_ops xf2440_ep_ops = {
	.alloc_request = xf2440_ep_alloc_request,
};



static struct xf2440_udc xf2440_udc_controller = {
	.gadget = {
		.name = "xf2440-udc",
		.ops = &xf2440_gadget_ops,
	},
	.ep[0] = {
				.name = "ep0",
				.ops = &xf2440_ep_ops,
				.maxpacket = FIFO_SIZE_8,
	},			
	
	.ep[1] = {
				.name = "ep1-bulk",
				.ops = &xf2440_ep_ops,
				.maxpacket = FIFO_SIZE_64,
	},
			
	.ep[2] = {
				.name = "ep2-bulk",
				.ops = &xf2440_ep_ops,
				.maxpacket = FIFO_SIZE_64,
	},
	
	.ep[3] =		{
				.name = "ep3-bulk",
				.ops = &xf2440_ep_ops,
				.maxpacket = FIFO_SIZE_64,
	},
	
	.ep[4] = {
				.name = "ep4-bulk",
				.ops = &xf2440_ep_ops,
				.maxpacket = FIFO_SIZE_64,
	},
};



int xf2440_udc_probe(void)
{
	int i;
	
	printf("XF2440: %s ================ \n", __func__);
	
	the_controller = &xf2440_udc_controller;

	the_controller->gadget.ep0 = &the_controller->ep[0];
	
	INIT_LIST_HEAD(&the_controller->gadget.ep_list);	
	INIT_LIST_HEAD(&the_controller->gadget.ep0->ep_list);

	/* basic endpoint records init */
	for (i = 0; i < XF2440_MAX_ENDPOINTS; i++) {
		struct usb_ep *ep = &the_controller->ep[i];

		if (i != 0)
			list_add_tail(&ep->ep_list, &the_controller->gadget.ep_list);

		//ep->desc = 0;
		//ep->stopped = 0;
		//INIT_LIST_HEAD(&ep->queue);
		//ep->pio_irqs = 0;
	}
	

	return 0;
}


int usb_gadget_handle_interrupts(int index)
{
	the_controller = &xf2440_udc_controller;	
	return xf2440_udc_irq(the_controller);
}


int usb_gadget_register_driver(struct usb_gadget_driver *driver)
{
	int retval = 0;
	struct xf2440_udc *dev;

	printf("XF2440: %s ================ \n", __func__);

	dev = the_controller;
	dev->driver = driver;


	retval = driver->bind(&dev->gadget);
	if (retval) {
		printf("%s: bind to driver --> error %d\n",
			    dev->gadget.name, retval);
		dev->driver = 0;
		return retval;
	}
	

	retval = xf2440_udc_enble(dev);
	if (retval) {
		printf("xf2440_udc_enble error \n");
		return retval;
	}
	
	
	return 0;
}

int usb_gadget_unregister_driver(struct usb_gadget_driver *driver)
{
	return 0;
}










#else



int s3c_udc_probe()
{
	return 0;
}

int usb_gadget_register_driver(struct usb_gadget_driver *driver)
{
	return 0;
}

int usb_gadget_unregister_driver(struct usb_gadget_driver *driver)
{
	return 0;
}


int usb_gadget_handle_interrupts(int index)
{
	return 0;
}

#endif
