import Stack from '@mui/material/Stack';
import ToggleButtonGroup from '@mui/material/ToggleButtonGroup';
import { type SelectProps } from '@mui/material/Select';

import StyledToggleButton from '@/ui/StyledToggleButton';

export interface JuceComboBoxProps
  extends Omit<
    SelectProps,
    | 'value'
    | 'onChange'
  > {
  value: number | string;
  // eslint-disable-next-line @typescript-eslint/no-explicit-any
  onChange: any;
  // eslint-disable-next-line @typescript-eslint/no-explicit-any
  choices: any;
}

export default function JuceComboBox({
  choices,
  ...props
}: JuceComboBoxProps) {
  const handleChange = (event: React.MouseEvent<HTMLElement>, nextValue: string) => {
    props.onChange(event, nextValue);
  };

  return (
    <Stack
      direction="row"
      alignItems="stretch"
      sx={{
        flexGrow:1,
        width: 'var(--knob-width)'
      }}
    >
      <ToggleButtonGroup
        orientation="vertical"
        value={props.value}
        exclusive
        onChange={handleChange}
        sx={{
          display:'flex',
          flexGrow:1,
        }}
      >
        {choices.map((choice: number | string, i: number) => (
          <StyledToggleButton
            key={i}
            value={i}
            label={choice}
          />
        ))}
      </ToggleButtonGroup>
    </Stack>
  );
}
