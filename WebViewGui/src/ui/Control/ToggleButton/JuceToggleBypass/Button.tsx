'use client';

import { PowerIcon } from '@phosphor-icons/react';
import { secondaryMain } from '@/define';
import IconButton, { type ExtendedButtonProps } from '@/ui/BlurIconButton';

interface JuceCheckboxProps extends ExtendedButtonProps {
  handleChange: (value: boolean) => void;
}

export default function JuceCheckbox({ value, handleChange, size = '1.5em' }: JuceCheckboxProps) {
  const handleMouseDown = () => {
    handleChange(!value);
  };

  return (
    <IconButton
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
