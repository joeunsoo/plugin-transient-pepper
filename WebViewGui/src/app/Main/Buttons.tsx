import Stack, { type StackProps } from '@mui/material/Stack';

import JuceToggleButton from '@/ui/Control/ToggleButton/JuceToggleButton';
import { uesControlStore } from '@/store/ControlStore';

export default function Page({
  ...props
}: StackProps) {
  const { setWetSolo } = uesControlStore();

  return (
    <Stack justifyContent="end" {...props}>
      <JuceToggleButton
        identifier="linkChannelsToggle"
        title={<>L/R<br />Link</>}
      />
      <JuceToggleButton
        identifier="wetSoloToggle"
        title={<>Wet<br />Solo</>}
        onChange={(e, value) => setWetSolo(value)}
      />
    </Stack>
  );
}
