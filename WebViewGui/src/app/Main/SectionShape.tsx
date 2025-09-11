import Stack, { type StackProps } from '@mui/material/Stack';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';
import SectionTitle from './SectionTitle';
import { msToString } from '@/utils/valueToString';
import AttackHigh from '@/ui/Icon/AttackHigh';
import AttackLow from '@/ui/Icon/AttackLow';
import ReleaseLow from '@/ui/Icon/ReleaseLow';
import ReleaseHigh from '@/ui/Icon/ReleaseHigh';

export default function Page({
  sx, ...props
}: StackProps) {
  return (
    <Stack
      direction="column"
      spacing="var(--row-spacing)"
      sx={{
        ...sx
      }}
      {...props}
    >
      <SectionTitle>
        Noise Shape
      </SectionTitle>
      <Stack
        direction="row"
        justifyContent="space-between"
        spacing="var(--column-spacing)"
        sx={{
          width: '100%',
          '--knob-width': '7.5em',
        }}
      >
        <JuceKnob
          identifier="attackSlider"
          defaultValue={0.5}
          valueToString={msToString}
          subDigit={1}
          color="secondary"
          lowIcon={<AttackLow />}
          highIcon={<AttackHigh />}
        />
        <JuceKnob
          identifier="releaseSlider"
          defaultValue={0.5}
          valueToString={msToString}
          subDigit={1}
          color="secondary"
          lowIcon={<ReleaseLow />}
          highIcon={<ReleaseHigh />}
        />
      </Stack>
    </Stack>
  );
}
