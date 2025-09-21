import chroma from 'chroma-js';
import type { MantineColorsTuple } from '@mantine/core';

export const primaryMain = '#535355';
export const secondaryMain = '#DF2926'; // #E53935 #FF4C4C
export const infoMain = '#6b3058';

export const secondaryDeep = '#420c0b';

export const themeColor = primaryMain;

interface PaletteProps {
  // eslint-disable-next-line @typescript-eslint/no-explicit-any
  [prop: string]: any;
}

export function generatePaletteMantine(
  color: string,
  deep: string = '#000000',
  centerIdx: number = 6
): MantineColorsTuple {
  const zero = centerIdx > 0 ? '#fff' : color;
  const forWhite = chroma
    .scale([zero, color])
    .mode('lab')
    .colors(centerIdx + 1);
  const forDeep = chroma
    .scale([color, deep])
    .mode('lab')
    .colors(10 - centerIdx)
    .slice(1);
  const array = [...forWhite, ...forDeep];

  const palette = array.slice(0, 10) as [
    string,
    string,
    string,
    string,
    string,
    string,
    string,
    string,
    string,
    string,
  ];

  return palette;
}
export function generatePaletteMantineOne(color: string): MantineColorsTuple {
  return chroma.scale(['#fff', color]).mode('lab').colors(10).slice(0, 10) as [
    string,
    string,
    string,
    string,
    string,
    string,
    string,
    string,
    string,
    string,
  ];
}

export function generatePaletteAlpha(color: string): MantineColorsTuple {
  return Array.from({ length: 10 }, (_, i) => {
    // i: 0 ~ 9
    const alpha = (i + 1) / 10; // 0.1 ~ 1.0
    return chroma(color).alpha(alpha).css(); // rgba(...) 형태
  }).slice(0, 10) as [
    string,
    string,
    string,
    string,
    string,
    string,
    string,
    string,
    string,
    string,
  ];
}

export const paletteMantine: PaletteProps = {
  primary: generatePaletteMantine(primaryMain),
  primaryLight: generatePaletteMantineOne(primaryMain),
  primaryDark: generatePaletteMantine(primaryMain, '#080808', 0),

  secondary: generatePaletteMantine(secondaryMain, secondaryDeep),
  secondaryLight: generatePaletteMantineOne(secondaryMain),
  secondaryDark: generatePaletteMantine(secondaryMain, '#160403', 0),
  info: generatePaletteMantine(infoMain),
};
