'use client';

import { PowerIcon } from '@phosphor-icons/react';
import IconButton, { type ExtendedButtonProps } from '@/ui/BlurIconButton';

interface JuceCheckboxProps extends ExtendedButtonProps {
  handleChange: (value: boolean) => void
}

export default function JuceCheckbox({
  value,
  handleChange,
  size='1.5em',
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
      w={size}
      h={size}
    >
      <PowerIcon
        weight="bold"
        size={size}
        color={value ? 'var(--mui-palette-secondary-main)' : 'var(--mui-palette-primary-darken)'}
      />
    </IconButton>
  );
}
