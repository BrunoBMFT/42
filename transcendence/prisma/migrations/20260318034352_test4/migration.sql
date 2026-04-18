/*
  Warnings:

  - You are about to drop the `UserPreferences` table. If the table is not empty, all the data it contains will be lost.

*/
-- DropForeignKey
ALTER TABLE "my_users" DROP CONSTRAINT "my_users_userPreferenceId_fkey";

-- DropTable
DROP TABLE "UserPreferences";

-- CreateTable
CREATE TABLE "UserPreference" (
    "id" TEXT NOT NULL,
    "emailUpdates" BOOLEAN NOT NULL,

    CONSTRAINT "UserPreference_pkey" PRIMARY KEY ("id")
);

-- AddForeignKey
ALTER TABLE "my_users" ADD CONSTRAINT "my_users_userPreferenceId_fkey" FOREIGN KEY ("userPreferenceId") REFERENCES "UserPreference"("id") ON DELETE SET NULL ON UPDATE CASCADE;
