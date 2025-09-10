import Stack, { type StackProps } from '@mui/material/Stack';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';
import { msToString } from '@/utils/valueToString';
import SectionTitle from './SectionTitle';

export default function Page({
  sx, ...props
}: StackProps) {
  return (
    <Stack
      direction="row"
      alignItems="center"
      alignContent="flex-start"
      justifyContent="center"
      spacing={2}
      sx={{
        backgroundColor: 'var(--mui-palette-info-darker)',
        border: '1px solid var(--mui-palette-info-darken)',
        boxShadow: `
          0 1px 2px rgba(0,0,0,0.2),
          inset 0 1px 0 rgba(255,255,255,0.5)
        `,
        borderRadius: 3,
        flexWrap: 'wrap',
        ...sx
      }}
      {...props}
    >
      <SectionTitle sx={{ width: '100%' }}>
        Shaping Noise
      </SectionTitle>
      <JuceKnob
        identifier="attackSlider"
        defaultValue={0.5}
        valueToString={msToString}
        subDigit={1}
      />
      <JuceKnob
        identifier="releaseSlider"
        defaultValue={0.5}
        valueToString={msToString}
        subDigit={1}
      />
      <JuceKnob
        identifier="tiltSlider"
        defaultValue={0.5}
        subDigit={1}
      />
      <JuceKnob
        identifier="midSideSlider"
        defaultValue={0.5}
        subDigit={1}
      />
    </Stack>
  );
}
