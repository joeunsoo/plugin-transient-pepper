import Stack from '@mui/material/Stack';
import ToggleButtonGroup from '@mui/material/ToggleButtonGroup';
import { type SelectProps } from '@mui/material/Select';

import StyledToggleButton from '@/src/ui/StyledToggleButton';

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
      alignItems="center"
      sx={{
        '& .MuiButtonBase-root': {
          px: 2,
          py: 1,
          color: 'var(--mui-palette-primary-light)',
          border: 'none',
          '& .button': {
            backgroundColor: 'var(--mui-palette-primary-darker)',
            fontWeight: 'var(--mui-fontWeight-lg)',
            borderRadius: '0.5em',
            border: '0.1em solid var(--mui-palette-grey)',
            px: '0.8em',
            boxShadow: `
              0em 0.3em 0.4em rgba(0,0,0,0.5),
              inset 0em 0.1em 0.4em rgba(255,255,255,0.3)
            `,
          },
          '&:hover, &.Mui-selected, &.Mui-selected:hover': {
            backgroundColor: 'transparent',
          },
          '&.Mui-selected': {
            color: 'unset',
            '& .button': {
              boxShadow: 'none',
              backgroundColor: 'var(--mui-palette-primary-lightest)',
              borderColor: 'var(--mui-palette-primary-light)',
            }
          },
        }
      }}
    >
      <ToggleButtonGroup
        orientation="vertical"
        value={props.value}
        exclusive
        onChange={handleChange}
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
