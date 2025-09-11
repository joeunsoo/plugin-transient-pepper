import Stack from '@mui/material/Stack';
import Box from '@mui/material/Box';
import Typography from '@mui/material/Typography';
import ToggleButton, { type ToggleButtonProps as MuiToggleButtonProps } from '@mui/material/ToggleButton';
import { LabelTypographySx, palette } from '@/define';
import { alpha } from '@mui/material/styles';

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
        width:'100%',
        justifyContent:'start',
        px: 1,
        py: 2,
        border: 'none',
        '& .button': {
          backgroundColor: 'var(--mui-palette-primary-darken)',
          fontWeight: 'var(--mui-fontWeight-lg)',
          border: '0.1em solid var(--mui-palette-primary-darker)',
          p: '0.8em',
          padding: '0.7em 1.8em',
          borderRadius: '999px',
          background: 'linear-gradient(135deg, var(--mui-palette-primary-dark), var(--mui-palette-primary-main))',
          boxShadow: `0 0.3em 0.4em ${alpha(palette.primary.darker, 0.5)}`,
        },
        '&:hover,  &.Mui-selected:hover': {
          backgroundColor: 'rgba(255,255,255,0.1)'
        },
        '&.Mui-selected': {
          backgroundColor: 'transparent',
          '& .button': {
            border: '0.1em solid var(--mui-palette-secondary-darker)',
            background: 'linear-gradient(135deg, var(--mui-palette-secondary-lightest), var(--mui-palette-common-white))',
            boxShadow: `0 0.25em 0.35em ${alpha(palette.secondary.darker, 0.4)}`,
            transform: 'translateY(2px)'
          }
        },
      }}
      {...props}
    >
      <Stack
        direction="row"
        alignItems="center"
        spacing={1.5}
      >
        <Box className="button" />
        <Typography
          sx={{
            ...LabelTypographySx,
          }}
        >
          {label}
        </Typography>
      </Stack>
    </ToggleButton>
  );
}
