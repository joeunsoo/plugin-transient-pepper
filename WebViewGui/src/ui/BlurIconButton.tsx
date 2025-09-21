import { ActionIcon, type ActionIconProps } from '@mantine/core';

export interface ExtendedButtonProps
  extends ActionIconProps,
  Omit<
    React.ButtonHTMLAttributes<HTMLButtonElement>,
    keyof ActionIconProps
  > {
}

export default function BlurIconButton(props: ExtendedButtonProps) {
  const { onMouseDown, onClick, ...rest } = props;

  const handleMouseDown = (e: React.MouseEvent<HTMLButtonElement>) => {
    onMouseDown?.(e);
    e.preventDefault();
  };

  const handleClick = (e: React.MouseEvent<HTMLButtonElement>) => {
    (e.currentTarget as HTMLElement).blur(); // 클릭 후 포커스 제거
    if (onClick) onClick(e);
  };

  return (
    <ActionIcon
      {...rest}
      onMouseDown={handleMouseDown}
      onClick={handleClick}
      variant="transparent"
      p={0}
    />
  );
}
