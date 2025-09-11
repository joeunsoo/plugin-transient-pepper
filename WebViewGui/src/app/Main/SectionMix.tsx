import Stack, { type StackProps } from '@mui/material/Stack';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';

import JuceToggleButton from '@/ui/Control/ToggleButton/JuceToggleButton';
import PeakMeterStereo from '@/ui/Meter/PeakMeterStereo';

import { uesControlStore } from '@/store/ControlStore';

export default function Page({
  sx, ...props
}: StackProps) {
  const { setBypass } = uesControlStore();

  return (
    <Stack
      direction="row"
      alignItems="center"
      justifyContent="end"
      spacing="var(--column-spacing)"
      sx={{
        '> *': {
          height: '100%',
        },
        ...sx
      }}
      {...props}
    >
      <Stack
        direction="column"
        alignItems="center"
        justifyContent="end"
        spacing="var(--row-spacing)"
      >
        <PeakMeterStereo
          idx={0}
          ignoreBypass
        />
        <JuceKnob
          identifier="outputGainSlider"
          defaultValue={0.5}
          subDigit={1}
          sx={{
            flexShrink: 0
          }}
          ignoreBypass
        />
      </Stack>
      <Stack
        direction="column"
        alignItems="center"
        justifyContent="end"
        spacing="var(--row-spacing)"
      >
        <Stack>
          <JuceToggleButton
            identifier="bypassToggle"
            title="Bypass"
            onChange={(e, value) => setBypass(value)}
            ignoreBypass
          />
          <JuceToggleButton
            identifier="linkChannelsToggle"
            title={<>L/R<br />Link</>}
          />
          <JuceToggleButton
            identifier="wetSoloToggle"
            title={<>Wet<br />Solo</>}
          />
        </Stack>

        <JuceKnob
          identifier="dryWetSlider"
          defaultValue={0.5}
          subDigit={1}
          sx={{
            flexShrink: 0
          }}
        />
      </Stack>
    </Stack>
  );
}
