import type { MantineColorsTuple } from '@mantine/core';
import chroma from 'chroma-js';

export const primaryMain = '#535355';
export const secondaryMain = '#DF2926'; // #E53935 #FF4C4C
export const infoMain = '#6b3058';

export const secondaryDeep = '#9c0a11';

export const themeColor = primaryMain;

interface PaletteProps {
  // eslint-disable-next-line @typescript-eslint/no-explicit-any
  [prop: string]: any
}

export function generatePaletteMantine(color: string, deep: string = '#000000'): MantineColorsTuple {
  const forWhite = chroma.scale(['#fff', color]).mode('lab').colors(7);
  const forDeep = chroma.scale([color, deep]).mode('lab').colors(4).slice(1);
  const array = [
    ...forWhite,
    ...forDeep
  ];

  const palette = array.slice(0, 10) as [
    string, string, string, string, string, string, string, string, string, string
  ];

  return palette;
}
export function generatePaletteMantineOne(color: string): MantineColorsTuple {
  return chroma.scale(['#fff', color]).mode('lab').colors(10).slice(0, 10) as [
    string, string, string, string, string, string, string, string, string, string
  ];
}

export function generatePaletteAlpha(color: string): MantineColorsTuple {
  return Array.from({ length: 10 }, (_, i) => {
    // i: 0 ~ 9
    const alpha = (i + 1) / 10; // 0.1 ~ 1.0
    return chroma(color).alpha(alpha).css(); // rgba(...) 형태
  }).slice(0, 10) as [
    string, string, string, string, string, string, string, string, string, string
  ];
}

export const paletteMantine:PaletteProps = {
  primary: generatePaletteMantine(primaryMain),
  secondary: generatePaletteMantine(secondaryMain, secondaryDeep),
  info: generatePaletteMantine(infoMain),
};
