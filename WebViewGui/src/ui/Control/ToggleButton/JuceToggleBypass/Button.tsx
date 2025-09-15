  'use client';

import PowerSettingsNewIcon from '@mui/icons-material/PowerSettingsNew';
import IconButton from '@/ui/BlurIconButton';

type JuceCheckboxProps = {
  value: boolean,
  handleChange: (value: boolean) => void
}

export default function JuceCheckbox({
  value,
  handleChange,
}: JuceCheckboxProps) {

  const handleMouseDown = () => {
    handleChange(!value);
  };

  return (
    <IconButton
      className={value ? 'Mui-selected' : ''}
      onMouseDown={() => {
        handleMouseDown();
      }}
      sx={{
        p:0,
        '& .MuiSvgIcon-root': {
        fill: value ? 'var(--mui-palette-secondary-main)' : 'var(--mui-palette-primary-darken)'
        }
      }}
    >
      <PowerSettingsNewIcon />
    </IconButton>
  );
}
