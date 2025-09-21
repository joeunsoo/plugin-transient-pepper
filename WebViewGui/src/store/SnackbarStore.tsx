import { create } from 'zustand';

interface Options {
  variant?: string;
}

const defaultOptions = {
  variant: 'primary',
};

interface SnackbarState {
  refreshCount: number;
  open: boolean; // 열기 여부
  message: string;
  options: Options;

  enqueueSnackbar: (message: string, options?: Options) => void; // 열기 여부 설정
  onClose: () => void; // 닫기
}

export const useSnackbarStore = create<SnackbarState>((set) => ({
  refreshCount: 0,
  open: false,
  message: '',
  options: {},
  enqueueSnackbar: (message: string, options?: Options) =>
    set((state) => ({
      refreshCount: state.refreshCount + 1,
      open: true,
      message,
      options: {
        ...defaultOptions,
        ...options,
      },
    })),
  onClose: () => set(() => ({ open: false })),
}));
