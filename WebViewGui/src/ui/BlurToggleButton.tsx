'use client';

import { Button, type ButtonProps } from '@mantine/core';
import { useUncontrolled } from '@mantine/hooks';
import type { MouseEvent } from 'react';

export interface BlurToggleButtonProps
  extends ButtonProps,
    Omit<
    React.ButtonHTMLAttributes<HTMLButtonElement>,
    keyof ButtonProps | 'onChange'
  > {
  checked?: boolean;
  defaultChecked?: boolean;
  onChange?: (checked: boolean) => void;
}

export default function BlurToggleButton(props: BlurToggleButtonProps) {
  const {
    checked,
    defaultChecked,
    onChange,
    ...rest
  } = props;

  // Mantine이 내부적으로 Checkbox 등에 쓰는 훅 (controlled/uncontrolled 패턴)
  const [value, setValue] = useUncontrolled({
    value: checked,
    defaultValue: defaultChecked,
    finalValue: false,
    onChange,
  });

  const handleClick = (e: MouseEvent<HTMLButtonElement>) => {
    (e.currentTarget as HTMLElement).blur(); // 클릭 후 포커스 제거
    setValue(!value);
  };

  return (
    <Button
      {...rest}
      variant={value ? 'filled' : 'light'}
      onClick={handleClick}
      data-value={value.valueOf()}
      h="2.35em"
    />
  );
}
