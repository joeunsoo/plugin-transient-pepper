'use client';

import { PowerIcon } from '@phosphor-icons/react';
import IconButton, { type ExtendedButtonProps } from '@/ui/BlurIconButton';
import { secondaryMain } from '@/define';

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
        color={value ? secondaryMain : 'var(--mantine-color-primary-7)'}
      />
    </IconButton>
  );
}
