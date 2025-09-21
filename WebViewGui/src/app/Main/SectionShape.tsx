import { Group, Stack, type StackProps } from '@mantine/core';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';
import SectionTitle from './SectionTitle';
import { msToString } from '@/utils/valueToString';
import AttackHigh from '@/ui/Icon/AttackHigh';
import AttackLow from '@/ui/Icon/AttackLow';
import ReleaseLow from '@/ui/Icon/ReleaseLow';
import ReleaseHigh from '@/ui/Icon/ReleaseHigh';
import { useControlStore } from '@/store/ControlStore';

export default function Page({
  sx, ...props
}: StackProps) {
  const { sidechainListen } = useControlStore();
  return (
    <Stack
      gap="var(--row-spacing)"
      sx={{
        ...sx
      }}
      {...props}
    >
      <SectionTitle
        addTest={[!sidechainListen]}
      >
        Noise Shape
      </SectionTitle>
      <Group
        justify="space-between"
        gap="var(--column-spacing)"
        sx={{
          width: '100%',
          '--knob-width': '8.0em',
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
          addTest={[!sidechainListen]}
        />
        <JuceKnob
          identifier="releaseSlider"
          defaultValue={0.5}
          valueToString={msToString}
          subDigit={1}
          color="secondary"
          lowIcon={<ReleaseLow />}
          highIcon={<ReleaseHigh />}
          addTest={[!sidechainListen]}
        />
      </Group>
    </Stack>
  );
}
