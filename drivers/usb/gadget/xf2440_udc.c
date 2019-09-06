/*
 * zhangqiang
 */
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

#define XF2440_UDC_EP0_FIFO					(XF2440_UDC_BASE + 0x1C0)



#define S3C2410_USBDREG(x) (x)

#define S3C2410_UDC_FUNC_ADDR_REG	S3C2410_USBDREG(0x0140)
#define S3C2410_UDC_PWR_REG		S3C2410_USBDREG(0x0144)
#define S3C2410_UDC_EP_INT_REG		S3C2410_USBDREG(0x0148)

#define S3C2410_UDC_USB_INT_REG		S3C2410_USBDREG(0x0158)
#define S3C2410_UDC_EP_INT_EN_REG	S3C2410_USBDREG(0x015c)

#define S3C2410_UDC_USB_INT_EN_REG	S3C2410_USBDREG(0x016c)

#define S3C2410_UDC_FRAME_NUM1_REG	S3C2410_USBDREG(0x0170)
#define S3C2410_UDC_FRAME_NUM2_REG	S3C2410_USBDREG(0x0174)

#define S3C2410_UDC_EP0_FIFO_REG	S3C2410_USBDREG(0x01c0)
#define S3C2410_UDC_EP1_FIFO_REG	S3C2410_USBDREG(0x01c4)
#define S3C2410_UDC_EP2_FIFO_REG	S3C2410_USBDREG(0x01c8)
#define S3C2410_UDC_EP3_FIFO_REG	S3C2410_USBDREG(0x01cc)
#define S3C2410_UDC_EP4_FIFO_REG	S3C2410_USBDREG(0x01d0)

#define S3C2410_UDC_EP1_DMA_CON		S3C2410_USBDREG(0x0200)
#define S3C2410_UDC_EP1_DMA_UNIT	S3C2410_USBDREG(0x0204)
#define S3C2410_UDC_EP1_DMA_FIFO	S3C2410_USBDREG(0x0208)
#define S3C2410_UDC_EP1_DMA_TTC_L	S3C2410_USBDREG(0x020c)
#define S3C2410_UDC_EP1_DMA_TTC_M	S3C2410_USBDREG(0x0210)
#define S3C2410_UDC_EP1_DMA_TTC_H	S3C2410_USBDREG(0x0214)

#define S3C2410_UDC_EP2_DMA_CON		S3C2410_USBDREG(0x0218)
#define S3C2410_UDC_EP2_DMA_UNIT	S3C2410_USBDREG(0x021c)
#define S3C2410_UDC_EP2_DMA_FIFO	S3C2410_USBDREG(0x0220)
#define S3C2410_UDC_EP2_DMA_TTC_L	S3C2410_USBDREG(0x0224)
#define S3C2410_UDC_EP2_DMA_TTC_M	S3C2410_USBDREG(0x0228)
#define S3C2410_UDC_EP2_DMA_TTC_H	S3C2410_USBDREG(0x022c)

#define S3C2410_UDC_EP3_DMA_CON		S3C2410_USBDREG(0x0240)
#define S3C2410_UDC_EP3_DMA_UNIT	S3C2410_USBDREG(0x0244)
#define S3C2410_UDC_EP3_DMA_FIFO	S3C2410_USBDREG(0x0248)
#define S3C2410_UDC_EP3_DMA_TTC_L	S3C2410_USBDREG(0x024c)
#define S3C2410_UDC_EP3_DMA_TTC_M	S3C2410_USBDREG(0x0250)
#define S3C2410_UDC_EP3_DMA_TTC_H	S3C2410_USBDREG(0x0254)

#define S3C2410_UDC_EP4_DMA_CON		S3C2410_USBDREG(0x0258)
#define S3C2410_UDC_EP4_DMA_UNIT	S3C2410_USBDREG(0x025c)
#define S3C2410_UDC_EP4_DMA_FIFO	S3C2410_USBDREG(0x0260)
#define S3C2410_UDC_EP4_DMA_TTC_L	S3C2410_USBDREG(0x0264)
#define S3C2410_UDC_EP4_DMA_TTC_M	S3C2410_USBDREG(0x0268)
#define S3C2410_UDC_EP4_DMA_TTC_H	S3C2410_USBDREG(0x026c)

#define S3C2410_UDC_INDEX_REG		S3C2410_USBDREG(0x0178)

/* indexed registers */

#define S3C2410_UDC_MAXP_REG		S3C2410_USBDREG(0x0180)

#define S3C2410_UDC_EP0_CSR_REG		S3C2410_USBDREG(0x0184)

#define S3C2410_UDC_IN_CSR1_REG		S3C2410_USBDREG(0x0184)
#define S3C2410_UDC_IN_CSR2_REG		S3C2410_USBDREG(0x0188)

#define S3C2410_UDC_OUT_CSR1_REG	S3C2410_USBDREG(0x0190)
#define S3C2410_UDC_OUT_CSR2_REG	S3C2410_USBDREG(0x0194)
#define S3C2410_UDC_OUT_FIFO_CNT1_REG	S3C2410_USBDREG(0x0198)
#define S3C2410_UDC_OUT_FIFO_CNT2_REG	S3C2410_USBDREG(0x019c)

#define S3C2410_UDC_FUNCADDR_UPDATE	(1 << 7)

#define S3C2410_UDC_PWR_ISOUP		(1 << 7) /* R/W */
#define S3C2410_UDC_PWR_RESET		(1 << 3) /* R   */
#define S3C2410_UDC_PWR_RESUME		(1 << 2) /* R/W */
#define S3C2410_UDC_PWR_SUSPEND		(1 << 1) /* R   */
#define S3C2410_UDC_PWR_ENSUSPEND	(1 << 0) /* R/W */

#define S3C2410_UDC_PWR_DEFAULT		(0x00)

#define S3C2410_UDC_INT_EP4		(1 << 4) /* R/W (clear only) */
#define S3C2410_UDC_INT_EP3		(1 << 3) /* R/W (clear only) */
#define S3C2410_UDC_INT_EP2		(1 << 2) /* R/W (clear only) */
#define S3C2410_UDC_INT_EP1		(1 << 1) /* R/W (clear only) */
#define S3C2410_UDC_INT_EP0		(1 << 0) /* R/W (clear only) */

#define S3C2410_UDC_USBINT_RESET	(1 << 2) /* R/W (clear only) */
#define S3C2410_UDC_USBINT_RESUME	(1 << 1) /* R/W (clear only) */
#define S3C2410_UDC_USBINT_SUSPEND	(1 << 0) /* R/W (clear only) */

#define S3C2410_UDC_INTE_EP4		(1 << 4) /* R/W */
#define S3C2410_UDC_INTE_EP3		(1 << 3) /* R/W */
#define S3C2410_UDC_INTE_EP2		(1 << 2) /* R/W */
#define S3C2410_UDC_INTE_EP1		(1 << 1) /* R/W */
#define S3C2410_UDC_INTE_EP0		(1 << 0) /* R/W */

#define S3C2410_UDC_USBINTE_RESET	(1 << 2) /* R/W */
#define S3C2410_UDC_USBINTE_SUSPEND	(1 << 0) /* R/W */

#define S3C2410_UDC_INDEX_EP0		(0x00)
#define S3C2410_UDC_INDEX_EP1		(0x01)
#define S3C2410_UDC_INDEX_EP2		(0x02)
#define S3C2410_UDC_INDEX_EP3		(0x03)
#define S3C2410_UDC_INDEX_EP4		(0x04)

#define S3C2410_UDC_ICSR1_CLRDT		(1 << 6) /* R/W */
#define S3C2410_UDC_ICSR1_SENTSTL	(1 << 5) /* R/W (clear only) */
#define S3C2410_UDC_ICSR1_SENDSTL	(1 << 4) /* R/W */
#define S3C2410_UDC_ICSR1_FFLUSH	(1 << 3) /* W   (set only) */
#define S3C2410_UDC_ICSR1_UNDRUN	(1 << 2) /* R/W (clear only) */
#define S3C2410_UDC_ICSR1_PKTRDY	(1 << 0) /* R/W (set only) */

#define S3C2410_UDC_ICSR2_AUTOSET	(1 << 7) /* R/W */
#define S3C2410_UDC_ICSR2_ISO		(1 << 6) /* R/W */
#define S3C2410_UDC_ICSR2_MODEIN	(1 << 5) /* R/W */
#define S3C2410_UDC_ICSR2_DMAIEN	(1 << 4) /* R/W */

#define S3C2410_UDC_OCSR1_CLRDT		(1 << 7) /* R/W */
#define S3C2410_UDC_OCSR1_SENTSTL	(1 << 6) /* R/W (clear only) */
#define S3C2410_UDC_OCSR1_SENDSTL	(1 << 5) /* R/W */
#define S3C2410_UDC_OCSR1_FFLUSH	(1 << 4) /* R/W */
#define S3C2410_UDC_OCSR1_DERROR	(1 << 3) /* R   */
#define S3C2410_UDC_OCSR1_OVRRUN	(1 << 2) /* R/W (clear only) */
#define S3C2410_UDC_OCSR1_PKTRDY	(1 << 0) /* R/W (clear only) */

#define S3C2410_UDC_OCSR2_AUTOCLR	(1 << 7) /* R/W */
#define S3C2410_UDC_OCSR2_ISO		(1 << 6) /* R/W */
#define S3C2410_UDC_OCSR2_DMAIEN	(1 << 5) /* R/W */

#define S3C2410_UDC_EP0_CSR_OPKRDY	(1 << 0)
#define S3C2410_UDC_EP0_CSR_IPKRDY	(1 << 1)
#define S3C2410_UDC_EP0_CSR_SENTSTL	(1 << 2)
#define S3C2410_UDC_EP0_CSR_DE		(1 << 3)
#define S3C2410_UDC_EP0_CSR_SE		(1 << 4)
#define S3C2410_UDC_EP0_CSR_SENDSTL	(1 << 5)
#define S3C2410_UDC_EP0_CSR_SOPKTRDY	(1 << 6)
#define S3C2410_UDC_EP0_CSR_SSE		(1 << 7)

#define S3C2410_UDC_MAXP_8		(1 << 0)
#define S3C2410_UDC_MAXP_16		(1 << 1)
#define S3C2410_UDC_MAXP_32		(1 << 2)
#define S3C2410_UDC_MAXP_64		(1 << 3)


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


#define EP0_PKT_SIZE             8	
#define EP1_PKT_SIZE             BULK_PKT_SIZE
#define EP3_PKT_SIZE             BULK_PKT_SIZE



#define CLR_EP0_OUT_PKT_RDY() 		writeb(((ep0_csr & (~EP0_WR_BITS)) | EP0_SERVICED_OUT_PKT_RDY ), XF2440_UDC_EP0_CSR_IN_CSR1_REG)	 
#define CLR_EP0_OUTPKTRDY_DATAEND() 	writeb(((ep0_csr & (~EP0_WR_BITS)) | (EP0_SERVICED_OUT_PKT_RDY | EP0_DATA_END)), XF2440_UDC_EP0_CSR_IN_CSR1_REG)
#define SET_EP0_IN_PKT_RDY() 		writeb(((ep0_csr & (~EP0_WR_BITS)) | (EP0_IN_PKT_READY)), XF2440_UDC_EP0_CSR_IN_CSR1_REG)	 
#define SET_EP0_INPKTRDY_DATAEND() 	writeb(((ep0_csr & (~EP0_WR_BITS)) | (EP0_IN_PKT_READY|EP0_DATA_END)), XF2440_UDC_EP0_CSR_IN_CSR1_REG)			
#define CLR_EP0_SETUP_END()		writeb(((ep0_csr & (~EP0_WR_BITS)) | (EP0_SERVICED_SETUP_END)), XF2440_UDC_EP0_CSR_IN_CSR1_REG)			
#define CLR_EP0_SENT_STALL() 		writeb(((ep0_csr & (~EP0_WR_BITS)) & (~EP0_SENT_STALL)), XF2440_UDC_EP0_CSR_IN_CSR1_REG)			
#define FLUSH_EP0_FIFO() 		{ while (readb(&usbdevregs->OUT_FIFO_CNT1_REG)) { readb(&usbdevregs->fifo[0].EP_FIFO_REG);}}

#if 0
#define dprintk(x...)	printf(x)
#else
#define dprintk(...)	

#endif

/* Warning : ep0 has a fifo of 16 bytes */
/* Don't try to set 32 or 64            */
/* also testusb 14 fails  wit 16 but is */
/* fine with 8                          */
#define EP0_FIFO_SIZE		 8
#define EP_FIFO_SIZE		64
#define DEFAULT_POWER_STATE	0x00
#define S3C2410_ENDPOINTS       ARRAY_SIZE(ep_name)


enum ep0_state {
        EP0_IDLE,
        EP0_IN_DATA_PHASE,
        EP0_OUT_DATA_PHASE,
        EP0_END_XFER,
        EP0_STALL,
};


struct s3c2410_ep {
	struct list_head		queue;
	unsigned long			last_io;	/* jiffies timestamp */
	struct usb_gadget		*gadget;
	struct s3c2410_udc		*dev;
	const struct usb_endpoint_descriptor *desc;
	struct usb_ep			ep;
	u8				num;

	unsigned short			fifo_size;
	u8				bEndpointAddress;
	u8				bmAttributes;

	unsigned			halted : 1;
	unsigned			already_seen : 1;
	unsigned			setup_stage : 1;
};

struct s3c2410_request {
	struct list_head		queue;		/* ep's requests */
	struct usb_request		req;
};


static const char ep0name [] = "ep0";

static const char *const ep_name[] = {
	ep0name,                                /* everyone has ep0 */
	/* s3c2410 four bidirectional bulk endpoints */
	"ep1-bulk", "ep2-bulk", "ep3-bulk", "ep4-bulk",
};

static const char *ep0states[]= {
        "EP0_IDLE",
        "EP0_IN_DATA_PHASE",
        "EP0_OUT_DATA_PHASE",
        "EP0_END_XFER",
        "EP0_STALL",
};

struct s3c2410_udc {
	spinlock_t			lock;

	struct s3c2410_ep		ep[S3C2410_ENDPOINTS];
	int				address;
	struct usb_gadget		gadget;
	struct usb_gadget_driver	*driver;
	struct s3c2410_request		fifo_req;
	u8				fifo_buf[EP_FIFO_SIZE];
	u16				devstatus;

	u32				port_status;
	int				ep0state;

	unsigned			got_irq : 1;

	unsigned			req_std : 1;
	unsigned			req_config : 1;
	unsigned			req_pending : 1;
	u8				vbus;
	struct dentry			*regs_info;
};

static const char		gadget_name[] = "s3c2410_udc";
static const char		driver_desc[] = "fdsafaf";




static void __iomem		*base_addr;


static struct s3c2410_udc *the_controller;



static inline struct s3c2410_ep *to_s3c2410_ep(struct usb_ep *ep)
{
	return container_of(ep, struct s3c2410_ep, ep);
}

static inline struct s3c2410_udc *to_s3c2410_udc(struct usb_gadget *gadget)
{
	return container_of(gadget, struct s3c2410_udc, gadget);
}

static inline struct s3c2410_request *to_s3c2410_req(struct usb_request *req)
{
	return container_of(req, struct s3c2410_request, req);
}


static inline u32 udc_read(u32 reg)
{
	return readb(base_addr + reg);
}

static inline void udc_write(u32 value, u32 reg)
{
	writeb(value, base_addr + reg);
}

static inline void udc_writeb(void __iomem *base, u32 value, u32 reg)
{
	writeb(value, base + reg);
}


static inline void s3c2410_udc_clear_ep0_opr(void __iomem *base)
{
	udc_writeb(base, S3C2410_UDC_INDEX_EP0, S3C2410_UDC_INDEX_REG);
	udc_writeb(base, S3C2410_UDC_EP0_CSR_SOPKTRDY,
			S3C2410_UDC_EP0_CSR_REG);
}

static inline void s3c2410_udc_clear_ep0_sst(void __iomem *base)
{
	udc_writeb(base, S3C2410_UDC_INDEX_EP0, S3C2410_UDC_INDEX_REG);
	writeb(0x00, base + S3C2410_UDC_EP0_CSR_REG);
}

static inline void s3c2410_udc_clear_ep0_se(void __iomem *base)
{
	udc_writeb(base, S3C2410_UDC_INDEX_EP0, S3C2410_UDC_INDEX_REG);
	udc_writeb(base, S3C2410_UDC_EP0_CSR_SSE, S3C2410_UDC_EP0_CSR_REG);
}

static inline void s3c2410_udc_set_ep0_ipr(void __iomem *base)
{
	udc_writeb(base, S3C2410_UDC_INDEX_EP0, S3C2410_UDC_INDEX_REG);
	udc_writeb(base, S3C2410_UDC_EP0_CSR_IPKRDY, S3C2410_UDC_EP0_CSR_REG);
}

static inline void s3c2410_udc_set_ep0_de(void __iomem *base)
{
	udc_writeb(base, S3C2410_UDC_INDEX_EP0, S3C2410_UDC_INDEX_REG);
	udc_writeb(base, S3C2410_UDC_EP0_CSR_DE, S3C2410_UDC_EP0_CSR_REG);
}

inline void s3c2410_udc_set_ep0_ss(void __iomem *b)
{
	udc_writeb(b, S3C2410_UDC_INDEX_EP0, S3C2410_UDC_INDEX_REG);
	udc_writeb(b, S3C2410_UDC_EP0_CSR_SENDSTL, S3C2410_UDC_EP0_CSR_REG);
}

static inline void s3c2410_udc_set_ep0_de_out(void __iomem *base)
{
	udc_writeb(base, S3C2410_UDC_INDEX_EP0, S3C2410_UDC_INDEX_REG);

	udc_writeb(base,(S3C2410_UDC_EP0_CSR_SOPKTRDY
				| S3C2410_UDC_EP0_CSR_DE),
			S3C2410_UDC_EP0_CSR_REG);
}

static inline void s3c2410_udc_set_ep0_sse_out(void __iomem *base)
{
	udc_writeb(base, S3C2410_UDC_INDEX_EP0, S3C2410_UDC_INDEX_REG);
	udc_writeb(base, (S3C2410_UDC_EP0_CSR_SOPKTRDY
				| S3C2410_UDC_EP0_CSR_SSE),
			S3C2410_UDC_EP0_CSR_REG);
}

static inline void s3c2410_udc_set_ep0_de_in(void __iomem *base)
{
	udc_writeb(base, S3C2410_UDC_INDEX_EP0, S3C2410_UDC_INDEX_REG);
	udc_writeb(base, (S3C2410_UDC_EP0_CSR_IPKRDY
			| S3C2410_UDC_EP0_CSR_DE),
		S3C2410_UDC_EP0_CSR_REG);
}






static void printHex(unsigned char *buf, int num)
{
	int i = 0;

	for(i = 0; i < num; ++i)
	{
		printf("%02x ", buf[i]);
	}
	printf("\n");
}


static inline int s3c2410_udc_fifo_count_out(void)
{
	int tmp;

	tmp = udc_read(S3C2410_UDC_OUT_FIFO_CNT2_REG) << 8;
	tmp |= udc_read(S3C2410_UDC_OUT_FIFO_CNT1_REG);
	return tmp;
}



/*------------------------- I/O ----------------------------------*/

/*
 *	s3c2410_udc_done
 */
static void s3c2410_udc_done(struct s3c2410_ep *ep,
		struct s3c2410_request *req, int status)
{
	unsigned halted = ep->halted;

	list_del_init(&req->queue);

	if (likely (req->req.status == -EINPROGRESS))
		req->req.status = status;
	else
		status = req->req.status;

	ep->halted = 1;
	req->req.complete(&ep->ep, &req->req);
	ep->halted = halted;
}

static void s3c2410_udc_nuke(struct s3c2410_udc *udc,
		struct s3c2410_ep *ep, int status)
{
	/* Sanity check */
	if (&ep->queue == NULL)
		return;

	while (!list_empty (&ep->queue)) {
		struct s3c2410_request *req;
		req = list_entry (ep->queue.next, struct s3c2410_request,
				queue);
		s3c2410_udc_done(ep, req, status);
	}
}


static void s3c2410_udc_hw_init(struct s3c2410_udc *dev)
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

	//printf("XF2440_UDC_OUT_CSR2_REG:0x%02x \n", readb(XF2440_UDC_OUT_CSR2_REG));
	//printf("XF2440_UDC_EP_INT_EN_REG:0x%02x \n", readb(XF2440_UDC_EP_INT_EN_REG));






	
    //    ep0State = EP0_STATE_INIT;
    
}

static int s3c2410_udc_read_fifo_crq(struct usb_ctrlrequest *crq)
{
	unsigned char *outbuf = (unsigned char*)crq;
	int bytes_read = 0;

	udc_write(0, S3C2410_UDC_INDEX_REG);

	bytes_read = s3c2410_udc_fifo_count_out();

	dprintk("%s: fifo_count=%d\n", __func__, bytes_read);

	if (bytes_read > sizeof(struct usb_ctrlrequest))
		bytes_read = sizeof(struct usb_ctrlrequest);

	readsb(S3C2410_UDC_EP0_FIFO_REG + base_addr, outbuf, bytes_read);

	dprintk("%s: len=%d %02x:%02x {%x,%x,%x}\n", __func__,
		bytes_read, crq->bRequest, crq->bRequestType,
		crq->wValue, crq->wIndex, crq->wLength);

	return bytes_read;
}


static int s3c2410_udc_enble(struct s3c2410_udc *dev)
{
	
	return 0;
}


static int s3c2410_udc_get_status(struct s3c2410_udc *dev,
		struct usb_ctrlrequest *crq)
{
	u16 status = 0;
	u8 ep_num = crq->wIndex & 0x7F;
	u8 is_in = crq->wIndex & USB_DIR_IN;

	switch (crq->bRequestType & USB_RECIP_MASK) {
	case USB_RECIP_INTERFACE:
		break;

	case USB_RECIP_DEVICE:
		status = dev->devstatus;
		break;

	case USB_RECIP_ENDPOINT:
		if (ep_num > 4 || crq->wLength > 2)
			return 1;

		if (ep_num == 0) {
			udc_write(0, S3C2410_UDC_INDEX_REG);
			status = udc_read(S3C2410_UDC_IN_CSR1_REG);
			status = status & S3C2410_UDC_EP0_CSR_SENDSTL;
		} else {
			udc_write(ep_num, S3C2410_UDC_INDEX_REG);
			if (is_in) {
				status = udc_read(S3C2410_UDC_IN_CSR1_REG);
				status = status & S3C2410_UDC_ICSR1_SENDSTL;
			} else {
				status = udc_read(S3C2410_UDC_OUT_CSR1_REG);
				status = status & S3C2410_UDC_OCSR1_SENDSTL;
			}
		}

		status = status ? 1 : 0;
		break;

	default:
		return 1;
	}

	/* Seems to be needed to get it working. ouch :( */
	udelay(5);
	udc_write(status & 0xFF, S3C2410_UDC_EP0_FIFO_REG);
	udc_write(status >> 8, S3C2410_UDC_EP0_FIFO_REG);
	s3c2410_udc_set_ep0_de_in(base_addr);

	return 0;
}




/*
 * s3c2410_udc_set_halt
 */
static int s3c2410_udc_set_halt(struct usb_ep *_ep, int value)
{
	struct s3c2410_ep	*ep = to_s3c2410_ep(_ep);
	u32			ep_csr = 0;
	unsigned long		flags;
	u32			idx;

	if (unlikely (!_ep || (!ep->desc && ep->ep.name != ep0name))) {
		dprintk("%s: inval 2\n", __func__);
		return -EINVAL;
	}

	local_irq_save (flags);

	idx = ep->bEndpointAddress & 0x7F;

	if (idx == 0) {
		s3c2410_udc_set_ep0_ss(base_addr);
		s3c2410_udc_set_ep0_de_out(base_addr);
	} else {
		udc_write(idx, S3C2410_UDC_INDEX_REG);
		ep_csr = udc_read((ep->bEndpointAddress &USB_DIR_IN)
				? S3C2410_UDC_IN_CSR1_REG
				: S3C2410_UDC_OUT_CSR1_REG);

		if ((ep->bEndpointAddress & USB_DIR_IN) != 0) {
			if (value)
				udc_write(ep_csr | S3C2410_UDC_ICSR1_SENDSTL,
					S3C2410_UDC_IN_CSR1_REG);
			else {
				ep_csr &= ~S3C2410_UDC_ICSR1_SENDSTL;
				udc_write(ep_csr, S3C2410_UDC_IN_CSR1_REG);
				ep_csr |= S3C2410_UDC_ICSR1_CLRDT;
				udc_write(ep_csr, S3C2410_UDC_IN_CSR1_REG);
			}
		} else {
			if (value)
				udc_write(ep_csr | S3C2410_UDC_OCSR1_SENDSTL,
					S3C2410_UDC_OUT_CSR1_REG);
			else {
				ep_csr &= ~S3C2410_UDC_OCSR1_SENDSTL;
				udc_write(ep_csr, S3C2410_UDC_OUT_CSR1_REG);
				ep_csr |= S3C2410_UDC_OCSR1_CLRDT;
				udc_write(ep_csr, S3C2410_UDC_OUT_CSR1_REG);
			}
		}
	}

	ep->halted = value ? 1 : 0;
	local_irq_restore (flags);

	return 0;
}

static int	s3c2410_udc_pullup (struct usb_gadget * gadget, int is_on)
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





/*
 *	s3c2410_udc_ep_enable
 */
static int s3c2410_udc_ep_enable(struct usb_ep *_ep,
				 const struct usb_endpoint_descriptor *desc)
{
	struct s3c2410_udc	*dev;
	struct s3c2410_ep	*ep;
	u32			max, tmp;
	unsigned long		flags;
	u32			csr1,csr2;
	u32			int_en_reg;

	ep = to_s3c2410_ep(_ep);

	if (!_ep || !desc || ep->desc
			|| _ep->name == ep0name
			|| desc->bDescriptorType != USB_DT_ENDPOINT)
		return -EINVAL;

	dev = ep->dev;
	if (!dev->driver || dev->gadget.speed == USB_SPEED_UNKNOWN)
		return -ESHUTDOWN;

	max = usb_endpoint_maxp(desc) & 0x1fff;

	local_irq_save (flags);
	_ep->maxpacket = max & 0x7ff;
	ep->desc = desc;
	ep->halted = 0;
	ep->bEndpointAddress = desc->bEndpointAddress;

	/* set max packet */
	udc_write(ep->num, S3C2410_UDC_INDEX_REG);
	udc_write(max >> 3, S3C2410_UDC_MAXP_REG);

	/* set type, direction, address; reset fifo counters */
	if (desc->bEndpointAddress & USB_DIR_IN) {
		csr1 = S3C2410_UDC_ICSR1_FFLUSH|S3C2410_UDC_ICSR1_CLRDT;
		csr2 = S3C2410_UDC_ICSR2_MODEIN|S3C2410_UDC_ICSR2_DMAIEN;

		udc_write(ep->num, S3C2410_UDC_INDEX_REG);
		udc_write(csr1, S3C2410_UDC_IN_CSR1_REG);
		udc_write(ep->num, S3C2410_UDC_INDEX_REG);
		udc_write(csr2, S3C2410_UDC_IN_CSR2_REG);
	} else {
		/* don't flush in fifo or it will cause endpoint interrupt */
		csr1 = S3C2410_UDC_ICSR1_CLRDT;
		csr2 = S3C2410_UDC_ICSR2_DMAIEN;

		udc_write(ep->num, S3C2410_UDC_INDEX_REG);
		udc_write(csr1, S3C2410_UDC_IN_CSR1_REG);
		udc_write(ep->num, S3C2410_UDC_INDEX_REG);
		udc_write(csr2, S3C2410_UDC_IN_CSR2_REG);

		csr1 = S3C2410_UDC_OCSR1_FFLUSH | S3C2410_UDC_OCSR1_CLRDT;
		csr2 = S3C2410_UDC_OCSR2_DMAIEN;

		udc_write(ep->num, S3C2410_UDC_INDEX_REG);
		udc_write(csr1, S3C2410_UDC_OUT_CSR1_REG);
		udc_write(ep->num, S3C2410_UDC_INDEX_REG);
		udc_write(csr2, S3C2410_UDC_OUT_CSR2_REG);
	}

	/* enable irqs */
	int_en_reg = udc_read(S3C2410_UDC_EP_INT_EN_REG);
	udc_write(int_en_reg | (1 << ep->num), S3C2410_UDC_EP_INT_EN_REG);

	/* print some debug message */
	tmp = desc->bEndpointAddress;
	dprintk ("enable %s(%d) ep%x%s-blk max %02x\n",
		 _ep->name,ep->num, tmp,
		 desc->bEndpointAddress & USB_DIR_IN ? "in" : "out", max);

	local_irq_restore (flags);
	s3c2410_udc_set_halt(_ep, 0);

	return 0;
}


/*
 * s3c2410_udc_ep_disable
 */
static int s3c2410_udc_ep_disable(struct usb_ep *_ep)
{
	struct s3c2410_ep *ep = to_s3c2410_ep(_ep);
	unsigned long flags;
	u32 int_en_reg;

	if (!_ep || !ep->desc) {
		dprintk("%s not enabled\n",
			_ep ? ep->ep.name : NULL);
		return -EINVAL;
	}

	local_irq_save(flags);

	dprintk("ep_disable: %s\n", _ep->name);

	ep->desc = NULL;
	ep->ep.desc = NULL;
	ep->halted = 1;

	s3c2410_udc_nuke (ep->dev, ep, -ESHUTDOWN);

	/* disable irqs */
	int_en_reg = udc_read(S3C2410_UDC_EP_INT_EN_REG);
	udc_write(int_en_reg & ~(1<<ep->num), S3C2410_UDC_EP_INT_EN_REG);

	local_irq_restore(flags);

	dprintk("%s disabled\n", _ep->name);

	return 0;
}




/*
 * s3c2410_udc_alloc_request
 */
static struct usb_request *
s3c2410_udc_alloc_request(struct usb_ep *_ep, gfp_t mem_flags)
{
	struct s3c2410_request *req;

	dprintk("%s(%p,%d)\n", __func__, _ep, mem_flags);

	if (!_ep)
		return NULL;

	req = kzalloc (sizeof(struct s3c2410_request), mem_flags);
	if (!req)
		return NULL;

	INIT_LIST_HEAD (&req->queue);
	return &req->req;
}

/*
 * s3c2410_udc_free_request
 */
static void
s3c2410_udc_free_request(struct usb_ep *_ep, struct usb_request *_req)
{
	struct s3c2410_ep	*ep = to_s3c2410_ep(_ep);
	struct s3c2410_request	*req = to_s3c2410_req(_req);

	dprintk("%s(%p,%p)\n", __func__, _ep, _req);

	if (!ep || !_req || (!ep->desc && _ep->name != ep0name))
		return;

	WARN_ON (!list_empty (&req->queue));
	kfree(req);
}

#if 0
static int s3c2410_udc_write_fifo(struct s3c2410_ep *ep,
		struct s3c2410_request *req)
{
	unsigned	count;
	int		is_last;
	u32		idx;
	int		fifo_reg;
	u32		ep_csr;

	idx = ep->bEndpointAddress & 0x7F;
	switch (idx) {
	default:
		idx = 0;
	case 0:
		fifo_reg = S3C2410_UDC_EP0_FIFO_REG;
		break;
	case 1:
		fifo_reg = S3C2410_UDC_EP1_FIFO_REG;
		break;
	case 2:
		fifo_reg = S3C2410_UDC_EP2_FIFO_REG;
		break;
	case 3:
		fifo_reg = S3C2410_UDC_EP3_FIFO_REG;
		break;
	case 4:
		fifo_reg = S3C2410_UDC_EP4_FIFO_REG;
		break;
	}

	count = s3c2410_udc_write_packet(fifo_reg, req, ep->ep.maxpacket);

	/* last packet is often short (sometimes a zlp) */
	if (count != ep->ep.maxpacket)
		is_last = 1;
	else if (req->req.length != req->req.actual || req->req.zero)
		is_last = 0;
	else
		is_last = 2;

	/* Only ep0 debug messages are interesting */
	if (idx == 0)
		dprintk(DEBUG_NORMAL,
			"Written ep%d %d.%d of %d b [last %d,z %d]\n",
			idx, count, req->req.actual, req->req.length,
			is_last, req->req.zero);

	if (is_last) {
		/* The order is important. It prevents sending 2 packets
		 * at the same time */

		if (idx == 0) {
			/* Reset signal => no need to say 'data sent' */
			if (! (udc_read(S3C2410_UDC_USB_INT_REG)
					& S3C2410_UDC_USBINT_RESET))
				s3c2410_udc_set_ep0_de_in(base_addr);
			ep->dev->ep0state=EP0_IDLE;
		} else {
			udc_write(idx, S3C2410_UDC_INDEX_REG);
			ep_csr = udc_read(S3C2410_UDC_IN_CSR1_REG);
			udc_write(idx, S3C2410_UDC_INDEX_REG);
			udc_write(ep_csr | S3C2410_UDC_ICSR1_PKTRDY,
					S3C2410_UDC_IN_CSR1_REG);
		}

		s3c2410_udc_done(ep, req, 0);
		is_last = 1;
	} else {
		if (idx == 0) {
			/* Reset signal => no need to say 'data sent' */
			if (! (udc_read(S3C2410_UDC_USB_INT_REG)
					& S3C2410_UDC_USBINT_RESET))
				s3c2410_udc_set_ep0_ipr(base_addr);
		} else {
			udc_write(idx, S3C2410_UDC_INDEX_REG);
			ep_csr = udc_read(S3C2410_UDC_IN_CSR1_REG);
			udc_write(idx, S3C2410_UDC_INDEX_REG);
			udc_write(ep_csr | S3C2410_UDC_ICSR1_PKTRDY,
					S3C2410_UDC_IN_CSR1_REG);
		}
	}

	return is_last;
}

#endif



/*
 *	s3c2410_udc_write_packet
 */
static inline int s3c2410_udc_write_packet(int fifo,
		struct s3c2410_request *req,
		unsigned max)
{
	unsigned len = min(req->req.length - req->req.actual, max);
	u8 *buf = req->req.buf + req->req.actual;

	prefetch(buf);

	dprintk("%s %d %d %d %d\n", __func__,
		req->req.actual, req->req.length, len, req->req.actual + len);

	req->req.actual += len;

	udelay(5);
	writesb(base_addr + fifo, buf, len);
	return len;
}



/*
 *	s3c2410_udc_write_fifo
 *
 * return:  0 = still running, 1 = completed, negative = errno
 */
static int s3c2410_udc_write_fifo(struct s3c2410_ep *ep,
		struct s3c2410_request *req)
{
	unsigned	count;
	int		is_last;
	u32		idx;
	int		fifo_reg;
	u32		ep_csr;

	idx = ep->bEndpointAddress & 0x7F;
	switch (idx) {
	default:
		idx = 0;
	case 0:
		fifo_reg = S3C2410_UDC_EP0_FIFO_REG;
		break;
	case 1:
		fifo_reg = S3C2410_UDC_EP1_FIFO_REG;
		break;
	case 2:
		fifo_reg = S3C2410_UDC_EP2_FIFO_REG;
		break;
	case 3:
		fifo_reg = S3C2410_UDC_EP3_FIFO_REG;
		break;
	case 4:
		fifo_reg = S3C2410_UDC_EP4_FIFO_REG;
		break;
	}

	count = s3c2410_udc_write_packet(fifo_reg, req, ep->ep.maxpacket);

	/* last packet is often short (sometimes a zlp) */
	if (count != ep->ep.maxpacket)
		is_last = 1;
	else if (req->req.length != req->req.actual || req->req.zero)
		is_last = 0;
	else
		is_last = 2;

	/* Only ep0 debug messages are interesting */
	if (idx == 0)
		dprintk("Written ep%d %d.%d of %d b [last %d,z %d]\n",
			idx, count, req->req.actual, req->req.length,
			is_last, req->req.zero);

	if (is_last) {
		/* The order is important. It prevents sending 2 packets
		 * at the same time */

		if (idx == 0) {
			/* Reset signal => no need to say 'data sent' */
			if (! (udc_read(S3C2410_UDC_USB_INT_REG)
					& S3C2410_UDC_USBINT_RESET))
				s3c2410_udc_set_ep0_de_in(base_addr);
			ep->dev->ep0state=EP0_IDLE;
		} else {
			udc_write(idx, S3C2410_UDC_INDEX_REG);
			ep_csr = udc_read(S3C2410_UDC_IN_CSR1_REG);
			udc_write(idx, S3C2410_UDC_INDEX_REG);
			udc_write(ep_csr | S3C2410_UDC_ICSR1_PKTRDY,
					S3C2410_UDC_IN_CSR1_REG);
		}

		s3c2410_udc_done(ep, req, 0);
		is_last = 1;
	} else {
		if (idx == 0) {
			/* Reset signal => no need to say 'data sent' */
			if (! (udc_read(S3C2410_UDC_USB_INT_REG)
					& S3C2410_UDC_USBINT_RESET))
				s3c2410_udc_set_ep0_ipr(base_addr);
		} else {
			udc_write(idx, S3C2410_UDC_INDEX_REG);
			ep_csr = udc_read(S3C2410_UDC_IN_CSR1_REG);
			udc_write(idx, S3C2410_UDC_INDEX_REG);
			udc_write(ep_csr | S3C2410_UDC_ICSR1_PKTRDY,
					S3C2410_UDC_IN_CSR1_REG);
		}
	}

	return is_last;
}



static inline int s3c2410_udc_read_packet(int fifo, u8 *buf,
		struct s3c2410_request *req, unsigned avail)
{
	unsigned len;

	len = min(req->req.length - req->req.actual, avail);
	req->req.actual += len;

	readsb(fifo + base_addr, buf, len);
	return len;
}



/*
 * return:  0 = still running, 1 = queue empty, negative = errno
 */
static int s3c2410_udc_read_fifo(struct s3c2410_ep *ep,
				 struct s3c2410_request *req)
{
	u8		*buf;
	u32		ep_csr;
	unsigned	bufferspace;
	int		is_last=1;
	unsigned	avail;
	int		fifo_count = 0;
	u32		idx;
	int		fifo_reg;

	idx = ep->bEndpointAddress & 0x7F;

	switch (idx) {
	default:
		idx = 0;
	case 0:
		fifo_reg = S3C2410_UDC_EP0_FIFO_REG;
		break;
	case 1:
		fifo_reg = S3C2410_UDC_EP1_FIFO_REG;
		break;
	case 2:
		fifo_reg = S3C2410_UDC_EP2_FIFO_REG;
		break;
	case 3:
		fifo_reg = S3C2410_UDC_EP3_FIFO_REG;
		break;
	case 4:
		fifo_reg = S3C2410_UDC_EP4_FIFO_REG;
		break;
	}

	if (!req->req.length)
		return 1;

	buf = req->req.buf + req->req.actual;
	bufferspace = req->req.length - req->req.actual;
	if (!bufferspace) {
		dprintk("%s: buffer full!\n", __func__);
		return -1;
	}

	udc_write(idx, S3C2410_UDC_INDEX_REG);

	fifo_count = s3c2410_udc_fifo_count_out();
	dprintk("%s fifo count : %d\n", __func__, fifo_count);

	if (fifo_count > ep->ep.maxpacket)
		avail = ep->ep.maxpacket;
	else
		avail = fifo_count;

	fifo_count = s3c2410_udc_read_packet(fifo_reg, buf, req, avail);

	/* checking this with ep0 is not accurate as we already
	 * read a control request
	 **/
	if (idx != 0 && fifo_count < ep->ep.maxpacket) {
		is_last = 1;
		/* overflowed this request?  flush extra data */
		if (fifo_count != avail)
			req->req.status = -EOVERFLOW;
	} else {
		is_last = (req->req.length <= req->req.actual) ? 1 : 0;
	}

	udc_write(idx, S3C2410_UDC_INDEX_REG);
	fifo_count = s3c2410_udc_fifo_count_out();

	/* Only ep0 debug messages are interesting */
	if (idx == 0)
		dprintk("%s fifo count : %d [last %d]\n",
			__func__, fifo_count,is_last);

	if (is_last) {
		if (idx == 0) {
			s3c2410_udc_set_ep0_de_out(base_addr);
			ep->dev->ep0state = EP0_IDLE;
		} else {
			udc_write(idx, S3C2410_UDC_INDEX_REG);
			ep_csr = udc_read(S3C2410_UDC_OUT_CSR1_REG);
			udc_write(idx, S3C2410_UDC_INDEX_REG);
			udc_write(ep_csr & ~S3C2410_UDC_OCSR1_PKTRDY,
					S3C2410_UDC_OUT_CSR1_REG);
		}

		s3c2410_udc_done(ep, req, 0);
	} else {
		if (idx == 0) {
			s3c2410_udc_clear_ep0_opr(base_addr);
		} else {
			udc_write(idx, S3C2410_UDC_INDEX_REG);
			ep_csr = udc_read(S3C2410_UDC_OUT_CSR1_REG);
			udc_write(idx, S3C2410_UDC_INDEX_REG);
			udc_write(ep_csr & ~S3C2410_UDC_OCSR1_PKTRDY,
					S3C2410_UDC_OUT_CSR1_REG);
		}
	}

	return is_last;
}



/*
 *	s3c2410_udc_queue
 */
static int s3c2410_udc_queue(struct usb_ep *_ep, struct usb_request *_req,
		gfp_t gfp_flags)
{
	struct s3c2410_request	*req = to_s3c2410_req(_req);
	struct s3c2410_ep	*ep = to_s3c2410_ep(_ep);
	struct s3c2410_udc	*dev;
	u32			ep_csr = 0;
	int			fifo_count = 0;
	unsigned long		flags;

	if (unlikely (!_ep || (!ep->desc && ep->ep.name != ep0name))) {
		dprintk("%s: invalid args\n", __func__);
		return -EINVAL;
	}

	dev = ep->dev;
	if (unlikely (!dev->driver
			|| dev->gadget.speed == USB_SPEED_UNKNOWN)) {
		return -ESHUTDOWN;
	}

	local_irq_save (flags);

	if (unlikely(!_req || !_req->complete
			|| !_req->buf || !list_empty(&req->queue))) {
		if (!_req)
			dprintk("%s: 1 X X X\n", __func__);
		else {
			dprintk("%s: 0 %01d %01d %01d\n",
				__func__, !_req->complete,!_req->buf,
				!list_empty(&req->queue));
		}

		local_irq_restore(flags);
		return -EINVAL;
	}

	_req->status = -EINPROGRESS;
	_req->actual = 0;

	dprintk("%s: ep%x len %d\n",
		 __func__, ep->bEndpointAddress, _req->length);

	if (ep->bEndpointAddress) {
		udc_write(ep->bEndpointAddress & 0x7F, S3C2410_UDC_INDEX_REG);

		ep_csr = udc_read((ep->bEndpointAddress & USB_DIR_IN)
				? S3C2410_UDC_IN_CSR1_REG
				: S3C2410_UDC_OUT_CSR1_REG);
		fifo_count = s3c2410_udc_fifo_count_out();
	} else {
		udc_write(0, S3C2410_UDC_INDEX_REG);
		ep_csr = udc_read(S3C2410_UDC_IN_CSR1_REG);
		fifo_count = s3c2410_udc_fifo_count_out();
	}

	dprintk("%s: zhangqiang  %01d %01d %01d\n",
				__func__, list_empty(&ep->queue),!ep->halted,
				dev->ep0state);

	/* kickstart this i/o queue? */
	if (list_empty(&ep->queue) && !ep->halted) 
	{
		if (ep->bEndpointAddress == 0 /* ep0 */) {
			switch (dev->ep0state) {
			case EP0_IN_DATA_PHASE:
				if (!(ep_csr&S3C2410_UDC_EP0_CSR_IPKRDY)
						&& s3c2410_udc_write_fifo(ep,
							req)) {
					dev->ep0state = EP0_IDLE;
					req = NULL;
				}
				break;

			case EP0_OUT_DATA_PHASE:
				if ((!_req->length)
					|| ((ep_csr & S3C2410_UDC_OCSR1_PKTRDY)
						&& s3c2410_udc_read_fifo(ep,
							req))) {
					dev->ep0state = EP0_IDLE;
					req = NULL;
				}
				break;

			default:
				local_irq_restore(flags);
				return -EL2HLT;
			}
		} else if ((ep->bEndpointAddress & USB_DIR_IN) != 0
				&& (!(ep_csr&S3C2410_UDC_OCSR1_PKTRDY))
				&& s3c2410_udc_write_fifo(ep, req)) {
			req = NULL;
		} else if ((ep_csr & S3C2410_UDC_OCSR1_PKTRDY)
				&& fifo_count
				&& s3c2410_udc_read_fifo(ep, req)) {
			req = NULL;
		}
	}

	/* pio or dma irq handler advances the queue. */
	if (likely (req != 0))
		list_add_tail(&req->queue, &ep->queue);

	local_irq_restore(flags);

	dprintk("%s ok\n", __func__);
	return 0;
}

/*
 *	s3c2410_udc_dequeue
 */
static int s3c2410_udc_dequeue(struct usb_ep *_ep, struct usb_request *_req)
{
	struct s3c2410_ep	*ep = to_s3c2410_ep(_ep);
	struct s3c2410_udc	*udc;
	int			retval = -EINVAL;
	unsigned long		flags;
	struct s3c2410_request	*req = NULL;

	dprintk("%s(%p,%p)\n", __func__, _ep, _req);

	if (!the_controller->driver)
		return -ESHUTDOWN;

	if (!_ep || !_req)
		return retval;

	udc = to_s3c2410_udc(ep->gadget);

	local_irq_save (flags);

	list_for_each_entry (req, &ep->queue, queue) {
		if (&req->req == _req) {
			list_del_init (&req->queue);
			_req->status = -ECONNRESET;
			retval = 0;
			break;
		}
	}

	if (retval == 0) {
		dprintk("dequeued req %p from %s, len %d buf %p\n",
			req, _ep->name, _req->length, _req->buf);

		s3c2410_udc_done(ep, req, -ECONNRESET);
	}

	local_irq_restore (flags);
	return retval;
}



static struct usb_gadget_ops s3c2410_ops = {
	.pullup = s3c2410_udc_pullup,
};

struct usb_ep_ops s3c2410_ep_ops = {
	.enable		= s3c2410_udc_ep_enable,
	.disable	= s3c2410_udc_ep_disable,
	
	.alloc_request = s3c2410_udc_alloc_request,
	.free_request	= s3c2410_udc_free_request,

	.queue		= s3c2410_udc_queue,
	.dequeue	= s3c2410_udc_dequeue,
	
	.set_halt	= s3c2410_udc_set_halt,
};

/*---------------------------------------------------------------------------*/
static struct s3c2410_udc memory = {
	.gadget = {
		.ops		= &s3c2410_ops,
		.ep0		= &memory.ep[0].ep,
		.name		= gadget_name,
	},

	/* control endpoint */
	.ep[0] = {
		.num		= 0,
		.ep = {
			.name		= ep0name,
			.ops		= &s3c2410_ep_ops,
			.maxpacket	= EP0_FIFO_SIZE,
		},
		.dev		= &memory,
	},

	/* first group of endpoints */
	.ep[1] = {
		.num		= 1,
		.ep = {
			.name		= "ep1-bulk",
			.ops		= &s3c2410_ep_ops,
			.maxpacket	= EP_FIFO_SIZE,
		},
		.dev		= &memory,
		.fifo_size	= EP_FIFO_SIZE,
		.bEndpointAddress = 1,
		.bmAttributes	= USB_ENDPOINT_XFER_BULK,
	},
	.ep[2] = {
		.num		= 2,
		.ep = {
			.name		= "ep2-bulk",
			.ops		= &s3c2410_ep_ops,
			.maxpacket	= EP_FIFO_SIZE,
		},
		.dev		= &memory,
		.fifo_size	= EP_FIFO_SIZE,
		.bEndpointAddress = 2,
		.bmAttributes	= USB_ENDPOINT_XFER_BULK,
	},
	.ep[3] = {
		.num		= 3,
		.ep = {
			.name		= "ep3-bulk",
			.ops		= &s3c2410_ep_ops,
			.maxpacket	= EP_FIFO_SIZE,
		},
		.dev		= &memory,
		.fifo_size	= EP_FIFO_SIZE,
		.bEndpointAddress = 3,
		.bmAttributes	= USB_ENDPOINT_XFER_BULK,
	},
	.ep[4] = {
		.num		= 4,
		.ep = {
			.name		= "ep4-bulk",
			.ops		= &s3c2410_ep_ops,
			.maxpacket	= EP_FIFO_SIZE,
		},
		.dev		= &memory,
		.fifo_size	= EP_FIFO_SIZE,
		.bEndpointAddress = 4,
		.bmAttributes	= USB_ENDPOINT_XFER_BULK,
	}

};

/*
 * s3c2410_udc_reinit
 */
static void s3c2410_udc_reinit(struct s3c2410_udc *dev)
{
	u32 i;

	/* device/ep0 records init */
	INIT_LIST_HEAD (&dev->gadget.ep_list);
	INIT_LIST_HEAD (&dev->gadget.ep0->ep_list);
	dev->ep0state = EP0_IDLE;

	for (i = 0; i < S3C2410_ENDPOINTS; i++) {
		struct s3c2410_ep *ep = &dev->ep[i];

		if (i != 0)
			list_add_tail (&ep->ep.ep_list, &dev->gadget.ep_list);

		ep->dev = dev;
		ep->desc = NULL;
		ep->ep.desc = NULL;
		ep->halted = 0;
		INIT_LIST_HEAD (&ep->queue);
	}
}


static void s3c2410_udc_handle_ep0_idle(struct s3c2410_udc *dev,
					struct s3c2410_ep *ep,
					struct usb_ctrlrequest *crq,
					u32 ep0csr)
{
	int len, ret, tmp;

	/* start control request? */
	if (!(ep0csr & S3C2410_UDC_EP0_CSR_OPKRDY))
		return;

	s3c2410_udc_nuke(dev, ep, -EPROTO);

	len = s3c2410_udc_read_fifo_crq(crq);
	if (len != sizeof(*crq)) {
		dprintk("setup begin: fifo READ ERROR"
			" wanted %d bytes got %d. Stalling out...\n",
			sizeof(*crq), len);
		s3c2410_udc_set_ep0_ss(base_addr);
		return;
	}

	dprintk("bRequest = %d bRequestType %d wLength = %d\n",
		crq->bRequest, crq->bRequestType, crq->wLength);

	/* cope with automagic for some standard requests. */
	dev->req_std = (crq->bRequestType & USB_TYPE_MASK)
		== USB_TYPE_STANDARD;
	dev->req_config = 0;
	dev->req_pending = 1;

	switch (crq->bRequest) {
	case USB_REQ_SET_CONFIGURATION:
		dprintk("USB_REQ_SET_CONFIGURATION ... \n");

		if (crq->bRequestType == USB_RECIP_DEVICE) {
			dev->req_config = 1;
			s3c2410_udc_set_ep0_de_out(base_addr);
		}
		break;

	case USB_REQ_SET_INTERFACE:
		dprintk("USB_REQ_SET_INTERFACE ... \n");

		if (crq->bRequestType == USB_RECIP_INTERFACE) {
			dev->req_config = 1;
			s3c2410_udc_set_ep0_de_out(base_addr);
		}
		break;

	case USB_REQ_SET_ADDRESS:
		dprintk("USB_REQ_SET_ADDRESS ... \n");

		if (crq->bRequestType == USB_RECIP_DEVICE) {
			tmp = crq->wValue & 0x7F;
			dev->address = tmp;
			udc_write((tmp | S3C2410_UDC_FUNCADDR_UPDATE),
					S3C2410_UDC_FUNC_ADDR_REG);
			s3c2410_udc_set_ep0_de_out(base_addr);
			return;
		}
		break;

	case USB_REQ_GET_STATUS:
		dprintk("USB_REQ_GET_STATUS ... \n");
		s3c2410_udc_clear_ep0_opr(base_addr);

		if (dev->req_std) {
			if (!s3c2410_udc_get_status(dev, crq)) {
				return;
			}
		}
		break;

	case USB_REQ_CLEAR_FEATURE:
		s3c2410_udc_clear_ep0_opr(base_addr);

		if (crq->bRequestType != USB_RECIP_ENDPOINT)
			break;

		if (crq->wValue != USB_ENDPOINT_HALT || crq->wLength != 0)
			break;

		s3c2410_udc_set_halt(&dev->ep[crq->wIndex & 0x7f].ep, 0);
		s3c2410_udc_set_ep0_de_out(base_addr);
		return;

	case USB_REQ_SET_FEATURE:
		s3c2410_udc_clear_ep0_opr(base_addr);

		if (crq->bRequestType != USB_RECIP_ENDPOINT)
			break;

		if (crq->wValue != USB_ENDPOINT_HALT || crq->wLength != 0)
			break;

		s3c2410_udc_set_halt(&dev->ep[crq->wIndex & 0x7f].ep, 1);
		s3c2410_udc_set_ep0_de_out(base_addr);
		return;

	default:
		s3c2410_udc_clear_ep0_opr(base_addr);
		break;
	}

	if (crq->bRequestType & USB_DIR_IN)
		dev->ep0state = EP0_IN_DATA_PHASE;
	else
		dev->ep0state = EP0_OUT_DATA_PHASE;

	if (!dev->driver)
		return;

	/* deliver the request to the gadget driver */
	ret = dev->driver->setup(&dev->gadget, crq);
	if (ret < 0) {
		if (dev->req_config) {
			dprintk("config change %02x fail %d?\n",
				crq->bRequest, ret);
			return;
		}

		if (ret == -EOPNOTSUPP)
			dprintk("Operation not supported\n");
		else
			dprintk("dev->driver->setup failed. (%d)\n", ret);

		udelay(5);
		s3c2410_udc_set_ep0_ss(base_addr);
		s3c2410_udc_set_ep0_de_out(base_addr);
		dev->ep0state = EP0_IDLE;
		/* deferred i/o == no response yet */
	} else if (dev->req_pending) {
		dprintk("dev->req_pending... what now?\n");
		dev->req_pending=0;
	}

	dprintk("ep0state %s\n", ep0states[dev->ep0state]);
}



static void s3c2410_udc_handle_ep0(struct s3c2410_udc *dev)
{
	u32			ep0csr;
	struct s3c2410_ep	*ep = &dev->ep[0];
	struct s3c2410_request	*req;
	struct usb_ctrlrequest	crq;

	if (list_empty(&ep->queue))
		req = NULL;
	else
		req = list_entry(ep->queue.next, struct s3c2410_request, queue);

	/* We make the assumption that S3C2410_UDC_IN_CSR1_REG equal to
	 * S3C2410_UDC_EP0_CSR_REG when index is zero */

	udc_write(0, S3C2410_UDC_INDEX_REG);
	ep0csr = udc_read(S3C2410_UDC_IN_CSR1_REG);

	dprintk("ep0csr %x ep0state %s\n",
		ep0csr, ep0states[dev->ep0state]);

	/* clear stall status */
	if (ep0csr & S3C2410_UDC_EP0_CSR_SENTSTL) {
		s3c2410_udc_nuke(dev, ep, -EPIPE);
		dprintk("... clear SENT_STALL ...\n");
		s3c2410_udc_clear_ep0_sst(base_addr);
		dev->ep0state = EP0_IDLE;
		return;
	}

	/* clear setup end */
	if (ep0csr & S3C2410_UDC_EP0_CSR_SE) {
		dprintk("... serviced SETUP_END ...\n");
		s3c2410_udc_nuke(dev, ep, 0);
		s3c2410_udc_clear_ep0_se(base_addr);
		dev->ep0state = EP0_IDLE;
	}

	switch (dev->ep0state) {
	case EP0_IDLE:
		s3c2410_udc_handle_ep0_idle(dev, ep, &crq, ep0csr);
		break;

	case EP0_IN_DATA_PHASE:			/* GET_DESCRIPTOR etc */
		dprintk("EP0_IN_DATA_PHASE ... what now?\n");
		if (!(ep0csr & S3C2410_UDC_EP0_CSR_IPKRDY) && req) {
			s3c2410_udc_write_fifo(ep, req);
		}
		break;

	case EP0_OUT_DATA_PHASE:		/* SET_DESCRIPTOR etc */
		dprintk("EP0_OUT_DATA_PHASE ... what now?\n");
		if ((ep0csr & S3C2410_UDC_EP0_CSR_OPKRDY) && req ) {
			s3c2410_udc_read_fifo(ep,req);
		}
		break;

	case EP0_END_XFER:
		dprintk("EP0_END_XFER ... what now?\n");
		dev->ep0state = EP0_IDLE;
		break;

	case EP0_STALL:
		dprintk("EP0_STALL ... what now?\n");
		dev->ep0state = EP0_IDLE;
		break;
	}
}



/*
 *	handle_ep - Manage I/O endpoints
 */

static void s3c2410_udc_handle_ep(struct s3c2410_ep *ep)
{
	struct s3c2410_request	*req;
	int			is_in = ep->bEndpointAddress & USB_DIR_IN;
	u32			ep_csr1;
	u32			idx;

	if (likely (!list_empty(&ep->queue)))
		req = list_entry(ep->queue.next,
				struct s3c2410_request, queue);
	else
		req = NULL;

	idx = ep->bEndpointAddress & 0x7F;

	if (is_in) {
		udc_write(idx, S3C2410_UDC_INDEX_REG);
		ep_csr1 = udc_read(S3C2410_UDC_IN_CSR1_REG);
		dprintk("ep%01d write csr:%02x %d\n",
			idx, ep_csr1, req ? 1 : 0);

		if (ep_csr1 & S3C2410_UDC_ICSR1_SENTSTL) {
			dprintk(DEBUG_VERBOSE, "st\n");
			udc_write(idx, S3C2410_UDC_INDEX_REG);
			udc_write(ep_csr1 & ~S3C2410_UDC_ICSR1_SENTSTL,
					S3C2410_UDC_IN_CSR1_REG);
			return;
		}

		if (!(ep_csr1 & S3C2410_UDC_ICSR1_PKTRDY) && req) {
			s3c2410_udc_write_fifo(ep,req);
		}
	} else {
		udc_write(idx, S3C2410_UDC_INDEX_REG);
		ep_csr1 = udc_read(S3C2410_UDC_OUT_CSR1_REG);
		dprintk("ep%01d rd csr:%02x\n", idx, ep_csr1);

		if (ep_csr1 & S3C2410_UDC_OCSR1_SENTSTL) {
			udc_write(idx, S3C2410_UDC_INDEX_REG);
			udc_write(ep_csr1 & ~S3C2410_UDC_OCSR1_SENTSTL,
					S3C2410_UDC_OUT_CSR1_REG);
			return;
		}

		if ((ep_csr1 & S3C2410_UDC_OCSR1_PKTRDY) && req) {
			s3c2410_udc_read_fifo(ep,req);
		}
	}
}



/*
 *	s3c2410_udc_irq - interrupt handler
 */
static irqreturn_t s3c2410_udc_irq(int dummy, void *_dev)
{
	struct s3c2410_udc *dev = _dev;
	int usb_status;
	int usbd_status;
	int pwr_reg;
	int ep0csr;
	int i;
	u32 idx, idx2;
	unsigned long flags;

	spin_lock_irqsave(&dev->lock, flags);

	/* Driver connected ? */
	if (!dev->driver) {
		/* Clear interrupts */
		udc_write(udc_read(S3C2410_UDC_USB_INT_REG),
				S3C2410_UDC_USB_INT_REG);
		udc_write(udc_read(S3C2410_UDC_EP_INT_REG),
				S3C2410_UDC_EP_INT_REG);
	}

	/* Save index */
	idx = udc_read(S3C2410_UDC_INDEX_REG);

	/* Read status registers */
	usb_status = udc_read(S3C2410_UDC_USB_INT_REG);
	usbd_status = udc_read(S3C2410_UDC_EP_INT_REG);
	pwr_reg = udc_read(S3C2410_UDC_PWR_REG);

	udc_writeb(base_addr, S3C2410_UDC_INDEX_EP0, S3C2410_UDC_INDEX_REG);
	ep0csr = udc_read(S3C2410_UDC_IN_CSR1_REG);

/*
	dprintk("usbs=%02x, usbds=%02x, pwr=%02x ep0csr=%02x\n",
		usb_status, usbd_status, pwr_reg, ep0csr);
		*/

	/*
	 * Now, handle interrupts. There's two types :
	 * - Reset, Resume, Suspend coming -> usb_int_reg
	 * - EP -> ep_int_reg
	 */

	/* RESET */
	if (usb_status & S3C2410_UDC_USBINT_RESET) {
		/* two kind of reset :
		 * - reset start -> pwr reg = 8
		 * - reset end   -> pwr reg = 0
		 **/
		dprintk("USB reset csr %x pwr %x\n",
			ep0csr, pwr_reg);

		dev->gadget.speed = USB_SPEED_UNKNOWN;
		udc_write(0x00, S3C2410_UDC_INDEX_REG);
		udc_write((dev->ep[0].ep.maxpacket & 0x7ff) >> 3,
				S3C2410_UDC_MAXP_REG);
		dev->address = 0;

		dev->ep0state = EP0_IDLE;
		dev->gadget.speed = USB_SPEED_FULL;

		/* clear interrupt */
		udc_write(S3C2410_UDC_USBINT_RESET,
				S3C2410_UDC_USB_INT_REG);

		udc_write(idx, S3C2410_UDC_INDEX_REG);
		spin_unlock_irqrestore(&dev->lock, flags);
		return IRQ_HANDLED;
	}

	/* RESUME */
	if (usb_status & S3C2410_UDC_USBINT_RESUME) {
		dprintk("USB resume\n");

		/* clear interrupt */
		udc_write(S3C2410_UDC_USBINT_RESUME,
				S3C2410_UDC_USB_INT_REG);

		if (dev->gadget.speed != USB_SPEED_UNKNOWN
				&& dev->driver
				&& dev->driver->resume)
			dev->driver->resume(&dev->gadget);
	}

	/* SUSPEND */
	if (usb_status & S3C2410_UDC_USBINT_SUSPEND) {
		dprintk("USB suspend\n");

		/* clear interrupt */
		udc_write(S3C2410_UDC_USBINT_SUSPEND,
				S3C2410_UDC_USB_INT_REG);

		if (dev->gadget.speed != USB_SPEED_UNKNOWN
				&& dev->driver
				&& dev->driver->suspend)
			dev->driver->suspend(&dev->gadget);

		dev->ep0state = EP0_IDLE;
	}

	/* EP */
	/* control traffic */
	/* check on ep0csr != 0 is not a good idea as clearing in_pkt_ready
	 * generate an interrupt
	 */
	if (usbd_status & S3C2410_UDC_INT_EP0) {
		dprintk("USB ep0 irq\n");
		/* Clear the interrupt bit by setting it to 1 */
		udc_write(S3C2410_UDC_INT_EP0, S3C2410_UDC_EP_INT_REG);
		s3c2410_udc_handle_ep0(dev);
	}

	
	/* endpoint data transfers */
	for (i = 1; i < S3C2410_ENDPOINTS; i++) {
		u32 tmp = 1 << i;
		if (usbd_status & tmp) {
			dprintk("USB ep%d irq\n", i);

			/* Clear the interrupt bit by setting it to 1 */
			udc_write(tmp, S3C2410_UDC_EP_INT_REG);
			s3c2410_udc_handle_ep(&dev->ep[i]);
		}
	}
	
	/* what else causes this interrupt? a receive! who is it? */
	if (!usb_status && !usbd_status && !pwr_reg && !ep0csr) {
		for (i = 1; i < S3C2410_ENDPOINTS; i++) {
			idx2 = udc_read(S3C2410_UDC_INDEX_REG);
			udc_write(i, S3C2410_UDC_INDEX_REG);

			if (udc_read(S3C2410_UDC_OUT_CSR1_REG) & 0x1)
				s3c2410_udc_handle_ep(&dev->ep[i]);

			/* restore index */
			udc_write(idx2, S3C2410_UDC_INDEX_REG);
		}
	}	

	/* Restore old index */
	udc_write(idx, S3C2410_UDC_INDEX_REG);

	spin_unlock_irqrestore(&dev->lock, flags);

	return IRQ_HANDLED;
}



int s3c2410_udc_probe(void)
{
	int i;
	
    printf("Init USB controller...\n");

	base_addr = (void *)XF2440_UDC_BASE;
	
	the_controller = &memory;

	the_controller->gadget.ep0 = &the_controller->ep[0].ep;
	
	s3c2410_udc_hw_init(the_controller);

	s3c2410_udc_reinit(the_controller);
	

	return 0;
}


int usb_gadget_handle_interrupts(int index)
{
	the_controller = &memory;	
	return s3c2410_udc_irq(0, the_controller);
}


int usb_gadget_register_driver(struct usb_gadget_driver *driver)
{
	int retval = 0;
	struct s3c2410_udc *dev;


	dev = the_controller;
	dev->driver = driver;


	retval = driver->bind(&dev->gadget);
	if (retval) {
		printf("%s: bind to driver --> error %d\n",
			    dev->gadget.name, retval);
		dev->driver = 0;
		return retval;
	}
	

	retval = s3c2410_udc_enble(dev);
	if (retval) {
		printf("s3c2410_udc_enble error \n");
		return retval;
	}
	
	
	return 0;
}

int usb_gadget_unregister_driver(struct usb_gadget_driver *driver)
{
	return 0;
}











