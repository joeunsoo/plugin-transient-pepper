import Stack, { type StackProps } from '@mui/material/Stack';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';
import SectionTitle from './SectionTitle';
import { msToString } from '@/utils/valueToString';

export default function Page({
  sx, ...props
}: StackProps) {
  return (
    <Stack
      direction="column"
      alignItems="center"
      justifyContent="stretch"
      spacing="var(--column-spacing)"
      sx={{
        ...sx
      }}
      {...props}
    >
      <SectionTitle>
        Noise Sculptor
      </SectionTitle>
      <Stack
        direction="row"
        justifyContent="center"
        sx={{
          flexGrow: 1,
          width: '100%',
          '--knob-width': '8.0em',
        }}
      >
      <JuceKnob
        identifier="attackSlider"
        defaultValue={0.5}
        valueToString={msToString}
        subDigit={1}
        ringColor="secondary"
        color="secondary"
      />
      <JuceKnob
        identifier="releaseSlider"
        defaultValue={0.5}
        valueToString={msToString}
        subDigit={1}
        ringColor="secondary"
        color="secondary"
      />
      </Stack>
    </Stack>
  );
}
