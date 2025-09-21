import type { MantineColorsTuple } from '@mantine/core';
import chroma from 'chroma-js';

export const primaryMain = '#111827'; // #c14f42, #0D47A1
export const secondaryMain = '#F43F5E'; // #F43F5E #3B82F6, #14B8A6, #F59E0B, #F43F5E
export const infoMain = '#4f5763';

export const secondaryDeep = '#aa0020';

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

export const primaryOklch: MantineColorsTuple = [
  'oklch(1 0.0 264.66)', // 0
  'oklch(0.87 0.0053 264.66)', // 1
  'oklch(0.74 0.0106 264.66)', // 2
  'oklch(0.61 0.0159 264.66)', // 3
  'oklch(0.48 0.0212 264.66)', // 4
  'oklch(0.35 0.0265 264.66)', // 5
  'oklch(0.2101 0.0318 264.66)', // 6
  'oklch(0.18 0.0212 264.66)', // 7
  'oklch(0.14 0.0106 264.66)', // 8
  'oklch(0.0 0.0 264.66)' // 9
];

export const secondaryOklch: MantineColorsTuple = [
  'oklch(1 0.0 16.44)', // 0
  'oklch(0.941 0.035 16.44)', // 1
  'oklch(0.882 0.070 16.44)', // 2
  'oklch(0.823 0.105 16.44)', // 3
  'oklch(0.764 0.140 16.44)', // 4
  'oklch(0.705 0.175 16.44)', // 5
  'oklch(0.645 0.2154 16.44)', // 6
  'oklch(0.586 0.2063 16.44)', // 7
  'oklch(0.527 0.1972 16.44)', // 8
  'oklch(0.4656 0.188 16.44)' // 9
];

export const infoOklch: MantineColorsTuple = [
  'oklch(1 0.0 258.37)', // 0
  'oklch(0.94 0.0024 258.37)', // 1
  'oklch(0.88 0.0048 258.37)', // 2
  'oklch(0.82 0.0072 258.37)', // 3
  'oklch(0.76 0.0096 258.37)', // 4
  'oklch(0.70 0.0120 258.37)', // 5
  'oklch(0.64 0.0144 258.37)', // 6
  'oklch(0.58 0.0168 258.37)', // 7
  'oklch(0.52 0.0192 258.37)', // 8
  'oklch(0.4542 0.0221 258.37)', // 9
];

export const paletteMantine:PaletteProps = {
  // primary: generatePaletteMantine(primaryMain),
  // secondary: generatePaletteMantine(secondaryMain, secondaryDeep),
  // info: generatePaletteMantineOne(infoMain),
  primary: primaryOklch,
  secondary: secondaryOklch,
  info: infoOklch,
  whiteAlpha: generatePaletteAlpha('#ffffff'),
};
