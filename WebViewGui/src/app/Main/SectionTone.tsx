import { Group, type GroupProps } from '@mantine/core';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';

export default function Page({
  ...props
}: GroupProps) {
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
      />
      <JuceKnob
        identifier="midSideSlider"
        defaultValue={0.5}
        subDigit={1}
      />
    </Group>
  );
}
