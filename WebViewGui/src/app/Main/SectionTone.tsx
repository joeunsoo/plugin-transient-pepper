import Stack, { type StackProps } from '@mui/material/Stack';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';
import JuceButtonGroup from '@/ui/Control/ComboBox/JuceButtonGroup';

export default function Page({
  ...props
}: StackProps) {
  return (
    <Stack
      direction="row"
      justifyContent="space-between"
      spacing="var(--column-spacing)"
      {...props}
    >
      <JuceButtonGroup
        identifier="generatorTypeCombo"
        hideTitle
      />
      <Stack
        direction="row"
        spacing="var(--column-spacing)"
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
      </Stack>
    </Stack>
  );
}
