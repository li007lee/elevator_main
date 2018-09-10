/* ========================================================================== */
/*                                                                            */
/*   Filename.c                                                               */
/*   (c) 2012 Author                                                          */
/*                                                                            */
/*   Description                                                              */
/*                                                                            */
/* ========================================================================== */

#include "my_include.h"
#include "md5gen.h"
#include "hf_plant_api.h"
#include "tcp_opt.h"
#include "udp_opt.h"
#include "file_opt.h"


//计算MD5
int calculate_md5(char *pDest, const char *pSrc)
{
	char buf[AUDIO_MAX_SIZE*2] = {0};

	snprintf(buf, sizeof(buf), "%skWbe3Nah3hjNpNdcRwlPtg", pSrc);
	md5_packages_string(pDest, buf, strlen(buf));

	return 1;
}


//mac_sn 网卡序列号, dev 网卡名
static HB_S32 get_mac_dev(HB_CHAR *mac_sn, HB_CHAR *dev)
{
    struct ifreq tmp;
    HB_S32 sock_mac;
   // HB_CHAR *tmpflag;
    //HB_CHAR mac_addr[30];
    sock_mac = socket(AF_INET, SOCK_STREAM, 0);
    if( sock_mac == -1)
    {
        perror("### create socket fail\n");
        return -1;
    }
    memset(&tmp,0,sizeof(tmp));
    strncpy(tmp.ifr_name, dev, sizeof(tmp.ifr_name)-1);
    if( (ioctl( sock_mac, SIOCGIFHWADDR, &tmp)) < 0 )
    {
    	close(sock_mac);
    	TRACE_ERR("### mac ioctl error\n");
        return -1;
    }

    close(sock_mac);
    memcpy(mac_sn, tmp.ifr_hwaddr.sa_data, 6);

    return 0;
}


//获取MAC
int get_sys_mac(char *sn, int sn_size)
{
	HB_CHAR get_mac[32] = {0};
	get_mac_dev(get_mac, ETHX);

    sprintf(sn, "%02x%02x%02x%02x%02x%02x",
            (HB_U8)get_mac[0],
            (HB_U8)get_mac[1],
            (HB_U8)get_mac[2],
            (HB_U8)get_mac[3],
            (HB_U8)get_mac[4],
            (HB_U8)get_mac[5]
            );

    return 0;
}

//获取网卡序列号
int get_sys_sn(char *sn, int sn_size)
{
	HB_CHAR get_mac[32] = {0};
	get_mac_dev(get_mac, ETHX);

    sprintf(sn, "%02x%02x%02x%02x",
            (HB_U8)get_mac[2],
            (HB_U8)get_mac[3],
            (HB_U8)get_mac[4],
            (HB_U8)get_mac[5]
            );

    return 0;
}
