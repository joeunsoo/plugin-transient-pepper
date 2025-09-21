// eslint-disable-next-line react-refresh/only-export-components
export * from './Plugin';

export {
  themeColor,
  paletteMantine,
  primaryMain,
  secondaryMain,
  infoMain,
} from './Color';

export const mantineSpace = 4;

export const meterStartColor = '#FF8F00';
export const meterEndColor = '#E53935';

export const LabelTypographySxWithoutColor = {
  fontSize: 'calc(var(--knob-width) * 0.15)',
  // fontSize: 'var(--mantine-font-size-sm)',
};

export const LabelTypographySx = {
  ...LabelTypographySxWithoutColor,
  color: 'var(--mantine-color-white)',
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
