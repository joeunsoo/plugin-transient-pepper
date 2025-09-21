import { Group, type GroupProps } from '@mantine/core';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';
import { useControlStore } from '@/store/ControlStore';
import { usePluginStore } from '@/store/PluginStore';

export default function Page({
  ...props
}: GroupProps) {
  const { sidechainListen } = useControlStore();
  const { numChannels } = usePluginStore();

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
        addTest={[!sidechainListen, numChannels < 2]}
      />
    </Group>
  );
}
