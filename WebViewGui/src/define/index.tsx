import {
  getContrastRatio,
  darken,
  lighten,
} from '@mui/material/styles';

export const toFixedDigits = 4;
export const PluginName = 'Transient Pepper';
export const PluginVersion = 'v1.0.0';
export const CompanyName = 'JoEunsoo';
export const CompanyWebsite = 'https://joeunsoo.com';

export const controlParameterIndexAnnotation = 'controlparameterindex';
export const AnalysisDataReceiverEventId = 'analysisData';
export const AnalysisDataReceiverLength = 16;

export function generatePalette(color: string) {
  return {
    main: color,

    whitest: lighten(color, 0.90),
    lightest: lighten(color, 0.85),
    lightermost: lighten(color, 0.70),
    lighter: lighten(color, 0.60),
    lightish: lighten(color, 0.50),
    lighten: lighten(color, 0.35),
    light: lighten(color, 0.2),

    dark: darken(color, 0.2),
    darken: darken(color, 0.35),
    darkish: darken(color, 0.50),
    darker: darken(color, 0.60),
    darkermost: darken(color, 0.70),
    darkest: darken(color, 0.85),
    blackest: darken(color, 0.90),
    contrastText: getContrastRatio(color, '#fff') > 2.5 ? '#fff' : '#111',
  };
}

export const primaryMain = '#535355';
export const secondaryMain = '#DF2926'; // #E53935 #FF4C4C
export const infoMain = '#6b3058';

interface PaletteProps {
  // eslint-disable-next-line @typescript-eslint/no-explicit-any
  [prop: string]: any
}

export const palette:PaletteProps = {
  primary: generatePalette(primaryMain),
  secondary: generatePalette(secondaryMain),
  info: generatePalette(infoMain)
};

export const meterStartColor = '#FF8F00';
export const meterEndColor = '#E53935';

export const noDragSx = {
  userSelect: 'none',
};

export const LabelTypographySxWithoutColor = {
  fontSize: 'calc(var(--knob-width) * 0.15)',
  // fontSize: 'var(--mui-fontSize-sm)',
};

export const LabelTypographySx = {
  ...LabelTypographySxWithoutColor,
  color: 'var(--mui-palette-common-white)',
};

export const GlassSx = {
  boxShadow: `
    inset 0 1px 1px rgba(255,255,255,0.1),
    inset 0 -1px 2px rgba(0,0,0,0.7),
    0 4px 8px rgba(0,0,0,0.5);
  `,
};

export const ignoreBypassOpacity = 0.5;

export function testOpacity(
  data: boolean[] // value
) {
  const result = data.find((item) => item);

  return result ? ignoreBypassOpacity : 1.0 ;
}
