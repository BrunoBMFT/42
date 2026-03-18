/*
  Warnings:

  - You are about to drop the column `userId` on the `UserPreferences` table. All the data in the column will be lost.
  - A unique constraint covering the columns `[userPreferenceId]` on the table `my_users` will be added. If there are existing duplicate values, this will fail.

*/
-- DropForeignKey
ALTER TABLE "UserPreferences" DROP CONSTRAINT "UserPreferences_userId_fkey";

-- DropIndex
DROP INDEX "UserPreferences_userId_key";

-- AlterTable
ALTER TABLE "UserPreferences" DROP COLUMN "userId";

-- AlterTable
ALTER TABLE "my_users" ADD COLUMN     "userPreferenceId" TEXT;

-- CreateIndex
CREATE UNIQUE INDEX "my_users_userPreferenceId_key" ON "my_users"("userPreferenceId");

-- AddForeignKey
ALTER TABLE "my_users" ADD CONSTRAINT "my_users_userPreferenceId_fkey" FOREIGN KEY ("userPreferenceId") REFERENCES "UserPreferences"("id") ON DELETE SET NULL ON UPDATE CASCADE;
