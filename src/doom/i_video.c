// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id:$
//
// Copyright (C) 1993-1996 by id Software, Inc.
//
// This source is available for distribution and/or modification
// only under the terms of the DOOM Source Code License as
// published by id Software. All rights reserved.
//
// The source is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// FITNESS FOR A PARTICULAR PURPOSE. See the DOOM Source Code License
// for more details.
//
// $Log:$
//
// DESCRIPTION:
//	DOOM graphics stuff for X11, UNIX.
//
//-----------------------------------------------------------------------------


#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

// Had to dig up XShm.c for this one.
// It is in the libXext, but not in the XFree86 headers.

#include <stdarg.h>

#include <sdk/os/lcd.h>
#include <sdk/calc/calc.h>

#include "doomstat.h"
#include "d_vars.h"
#include "i_system.h"
#include "i_keys.h"
#include "v_video.h"
#include "m_argv.h"
#include "d_main.h"

#include "doomdef.h"

#define POINTER_WARP_COUNTDOWN	1

typeof(*vram) cas_colors[sizeof(**screens) * ((1ul << CHAR_BIT) - 1)] __attribute__((section(".oc_mem.x.data")));

void I_ShutdownGraphics(void)
{
}

//
// I_StartFrame
//
void I_StartFrame (void)
{
    // er?

}

boolean		mousemoved = false;


void I_GetEvent(void)
{
    event_t event;

    if (I_GetKeyEvent(&event))
    {
        D_PostEvent(&event);
    }
}

//
// I_StartTic
//
void I_StartTic (void)
{
	I_GetEvent();
}


//
// I_UpdateNoBlit
//
void I_UpdateNoBlit (void)
{
    // what is this?
}

//
// I_FinishUpdate
//
void I_FinishUpdate (void)
{
    static int	lasttic;
    int		tics;
    int		i;

    // draws little dots on the bottom of the screen
    if (devparm)
    {
        i = I_GetTime();
        tics = i - lasttic;
        lasttic = i;
        if (tics > 20) tics = 20;

        for (i=0 ; i<tics*2 ; i+=2)
            screens[0][ (SCREENHEIGHT-1)*SCREENWIDTH + i] = 0xff;
        for ( ; i<20*2 ; i+=2)
            screens[0][ (SCREENHEIGHT-1)*SCREENWIDTH + i] = 0x0;
    }

    LCD_SetDrawingBounds(0, SCREENWIDTH - 1, (height - SCREENHEIGHT) / 2, (height + SCREENHEIGHT) / 2 - 1);
    LCD_SendCommand(COMMAND_PREPARE_FOR_DRAW_DATA);
    // maybe async dmac 2k chunks here? (compute from table while copying in the background)
    for (short y = 0; y < SCREENHEIGHT; y++)
    {
        for (short x = 0; x < SCREENWIDTH; x++) 
        {
            size_t pixel = (y * SCREENWIDTH) + x;
            *lcd_data_port = cas_colors[screens[0][pixel]];
        }
    }
}


//
// I_ReadScreen
//
void I_ReadScreen (byte* scr)
{
    memcpy (scr, screens[0], SCREENWIDTH*SCREENHEIGHT);
}

//
// I_SetPalette
//
void I_SetPalette (byte* palette)
{
    for (size_t i = 0; i < sizeof(cas_colors) / sizeof(*cas_colors); i++)
    {
        byte red = ((gammatable[usegamma][*palette++] * 0x20) / 0x100);
        byte green = ((gammatable[usegamma][*palette++] * 0x40) / 0x100);
        byte blue = ((gammatable[usegamma][*palette++] * 0x20) / 0x100);
        
        cas_colors[i] = RGB_TO_RGB565(red, green, blue);
    }
}

void I_InitGraphics(void)
{
    int			n;
    int			pnum;
    int			x=0;
    int			y=0;
    
    // warning: char format, different type arg
    char		xsign=' ';
    char		ysign=' ';

    static int		firsttime=1;

    if (!firsttime)
	    return;

    firsttime = 0;

    // check for command-line geometry
    if ( (pnum=M_CheckParm("-geom")) ) // suggest parentheses around assignment
    {
        // warning: char format, different type arg 3,5
        n = sscanf(myargv[pnum+1], "%c%d%c%d", &xsign, &x, &ysign, &y);
        
        if (n==2)
            x = y = 0;
        else if (n==6)
        {
            if (xsign == '-')
            x = -x;
            if (ysign == '-')
            y = -y;
        }
        else
            I_Error("bad -geom parameter");
    }
}

