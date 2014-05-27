/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loadcolor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdefilip <vdefilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/24 17:00:58 by vdefilip          #+#    #+#             */
/*   Updated: 2014/05/24 17:00:58 by vdefilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	load_tab_color1(int *tab)
{
	tab[3959] = 0xf0f8ff;
	tab[2045] = 0xfaebd7;
	tab[1005] = 0x00ffff;
	tab[713] = 0x7fffd4;
	tab[360] = 0xf0ffff;
	tab[1073] = 0xf5f5dc;
	tab[2882] = 0xffe4c4;
	tab[2994] = 0x000000;
	tab[1525] = 0xffebcd;
	tab[1401] = 0x0000ff;
	tab[616] = 0x8a2be2;
	tab[2325] = 0xa52a2a;
	tab[3416] = 0xdeb887;
	tab[3850] = 0x5f9ea0;
	tab[1343] = 0x7fff00;
	tab[515] = 0xd2691e;
	tab[3674] = 0xff7f50;
	tab[1606] = 0x6495ed;
	tab[2286] = 0xfff8dc;
	tab[16] = 0xdc143c;
	tab[3544] = 0x00ffff;
	tab[1163] = 0x00008b;
	tab[3306] = 0x008b8b;
	tab[4157] = 0xb8860b;
	tab[1842] = 0xa9a9a9;
}

void	load_tab_color2(int *tab)
{
	tab[92] = 0x006400;
	tab[2843] = 0xbdb76b;
	tab[764] = 0x8b008b;
	tab[3867] = 0x556b2f;
	tab[2403] = 0xff8c00;
	tab[3308] = 0x9932cc;
	tab[790] = 0x8b0000;
	tab[3409] = 0xe9967a;
	tab[3405] = 0x8fbc8f;
	tab[3368] = 0x483d8b;
	tab[4047] = 0x2f4f4f;
	tab[780] = 0x00ced1;
	tab[2854] = 0x9400d3;
	tab[2961] = 0xff1493;
	tab[998] = 0x00bfff;
	tab[3370] = 0x696969;
	tab[2914] = 0x1e90ff;
	tab[1514] = 0xb22222;
	tab[1662] = 0xfffaf0;
	tab[1621] = 0x228b22;
	tab[1380] = 0xff00ff;
	tab[3453] = 0xdcdcdc;
	tab[1383] = 0xf8f8ff;
	tab[3455] = 0xffd700;
	tab[2715] = 0xdaa520;
}

void	load_tab_color3(int *tab)
{
	tab[2080] = 0x808080;
	tab[3646] = 0x008000;
	tab[2014] = 0xadff2f;
	tab[968] = 0xf0fff0;
	tab[1998] = 0xff69b4;
	tab[959] = 0xcd5c5c;
	tab[4019] = 0x4b0082;
	tab[2166] = 0xfffff0;
	tab[2097] = 0xf0e68c;
	tab[542] = 0xe6e6fa;
	tab[1932] = 0xfff0f5;
	tab[844] = 0x7cfc00;
	tab[1981] = 0xfffacd;
	tab[1921] = 0xadd8e6;
	tab[3634] = 0xf08080;
	tab[4064] = 0xe0ffff;
	tab[4235] = 0xfafad2;
	tab[2600] = 0xd3d3d3;
	tab[3606] = 0x90ee90;
	tab[2747] = 0xffb6c1;
	tab[547] = 0xffa07a;
	tab[2359] = 0x20b2aa;
	tab[1028] = 0x87cefa;
	tab[3141] = 0x778899;
	tab[1506] = 0xb0c4de;
}

void	load_tab_color4(int *tab)
{
	tab[2509] = 0xffffe0;
	tab[340] = 0x00ff00;
	tab[2133] = 0x32cd32;
	tab[3819] = 0xfaf0e6;
	tab[3794] = 0xff00ff;
	tab[833] = 0x800000;
	tab[4130] = 0x66cdaa;
	tab[3602] = 0x0000cd;
	tab[1403] = 0xba55d3;
	tab[1626] = 0x9370db;
	tab[3344] = 0x3cb371;
	tab[75] = 0x7b68ee;
	tab[1594] = 0x00fa9a;
	tab[1787] = 0x48d1cc;
	tab[3760] = 0xc71585;
	tab[2473] = 0x191970;
	tab[721] = 0xf5fffa;
	tab[1204] = 0xffe4e1;
	tab[558] = 0xffe4b5;
	tab[49] = 0xffdead;
	tab[3619] = 0x000080;
	tab[637] = 0xfdf5e6;
	tab[900] = 0x808000;
	tab[1745] = 0x6b8e23;
	tab[3585] = 0xffa500;
}

int		*ft_loadcolor(void)
{
	static int		tab[5000];
	static int		set = 0;

	if (!set)
	{
		set = 1;
		load_tab_color1(tab);
		load_tab_color2(tab);
		load_tab_color3(tab);
		load_tab_color4(tab);
		load_tab_color5(tab);
		load_tab_color6(tab);
	}
	return (tab);
}
