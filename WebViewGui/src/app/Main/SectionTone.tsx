import { Group, type GroupProps } from '@mantine/core';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';
import { uesControlStore } from '@/store/ControlStore';

export default function Page({
  ...props
}: GroupProps) {
  const { sidechainListen } = uesControlStore();

  return (
    <Group
      justify="flex-end"
      gap="var(--column-spacing)"
      {...props}
    >
      <JuceKnob
        identifier="tiltSlider"
        defaultValue={0.5}
        subDigit={1}
        addTest={[!sidechainListen]}
      />
      <JuceKnob
        identifier="midSideSlider"
        defaultValue={0.5}
        subDigit={1}
        addTest={[!sidechainListen]}
      />
    </Group>
  );
}
