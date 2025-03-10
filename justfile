build:
    pnpm run build

deploy: build
    cd apps/web && vercel