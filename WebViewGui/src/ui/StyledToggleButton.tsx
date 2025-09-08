import Stack from '@mui/material/Stack';
import Box from '@mui/material/Box';
import Typography from '@mui/material/Typography';
import ToggleButton, { type ToggleButtonProps as MuiToggleButtonProps } from '@mui/material/ToggleButton';

export interface ToggleButtonProps
  extends MuiToggleButtonProps {
  label: string | number
}

export default function JuceComboBox({
  label,
  ...props
}: ToggleButtonProps) {

  return (
    <ToggleButton
      disableRipple
      sx={{
        px: 2,
        py: 2.2,
        color: 'var(--mui-palette-text-disabled)',
        border: 'none',
        '& .button': {
          backgroundColor: 'var(--mui-palette-primary-darken)',
          fontWeight: 'var(--mui-fontWeight-lg)',
          borderRadius: '0.5em',
          border: '0.1em solid var(--mui-palette-primary-darker)',
          p: '0.8em',
          boxShadow: '0em 0.3em 0.4em rgba(0,0,0,0.5)',
        },
        '&:hover, &.Mui-selected, &.Mui-selected:hover': {
          backgroundColor: 'transparent',
        },
        '&.Mui-selected': {
          color: 'unset',
          '& .button': {
            // boxShadow: 'none',
            backgroundColor: 'var(--mui-palette-primary-lightest)',
          }
        },
      }}
      {...props}
    >
      <Stack
        direction="row"
        alignItems="center"
        spacing={2}
      >
        <Box className="button" />
        <Typography>
          {label}
        </Typography>
      </Stack>
    </ToggleButton>
  );
}
