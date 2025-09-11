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
        border: '0.1em solid var(--mui-palette-primary-darkest)',
        my: '0.2em',
        py: '0.5em',
        borderRadius: '0.3em',
        background: 'linear-gradient(135deg, var(--mui-palette-secondary-darker), var(--mui-palette-secondary-blackest))',
        ...GlassSx,
        '&.Mui-selected': {
          background: 'linear-gradient(135deg, var(--mui-palette-secondary-main), var(--mui-palette-secondary-dark))',
        },
      }}
      {...props}
    >
      <Typography
        sx={{
          ...LabelTypographySx,
        }}
      >
        {label}
      </Typography>
    </ToggleButton>
  );
}
