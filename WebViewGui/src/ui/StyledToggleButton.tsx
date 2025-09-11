import Stack from '@mui/material/Stack';
import Box from '@mui/material/Box';
import Typography from '@mui/material/Typography';
import ToggleButton, { type ToggleButtonProps as MuiToggleButtonProps } from '@mui/material/ToggleButton';
import { GlassSx, LabelTypographySx } from '@/define';

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
        width: '100%',
        justifyContent: 'start',
        px: 1,
        py: 2,
        border: 'none',
        '& .button': {
          backgroundColor: 'var(--mui-palette-primary-darken)',
          fontWeight: 'var(--mui-fontWeight-lg)',
          border: '0.1em solid var(--mui-palette-primary-darkest)',
          p: '0.8em',
          padding: '0.7em 1.2em',
          borderRadius: '999px',
          background: 'linear-gradient(135deg, var(--mui-palette-secondary-darker), var(--mui-palette-secondary-blackest))',
          ...GlassSx,
          transform: 'translateY(-1px)'
        },
        '&:hover,  &.Mui-selected:hover': {
          backgroundColor: 'rgba(255,255,255,0.1)'
        },
        '&.Mui-selected': {
          backgroundColor: 'transparent',
          '& .button': {
            background: 'linear-gradient(135deg, var(--mui-palette-secondary-main), var(--mui-palette-secondary-dark))',
            ...GlassSx,
            transform: 'translateY(1px)'
          }
        },
      }}
      {...props}
    >
      <Stack
        direction="row"
        alignItems="center"
        spacing={1.5}
        sx={{
          flexGrow: 1,
        }}
      >
        <Box className="button" />
        <Stack
          alignItems="center"
          justifyContent="center"
          sx={{
            flexGrow: 1,
          }}
        >
          <Typography
            sx={{
              ...LabelTypographySx,
              textAlign: 'center',
            }}
          >
            {label}
          </Typography>
        </Stack>
      </Stack>
    </ToggleButton>
  );
}
