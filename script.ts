//so many awaits, this is ugly
import { PrismaClient } from "@prisma/client";
const prisma = new PrismaClient()

//just testing
async function deleteAllUsers() {
	await prisma.my_users.deleteMany()//!THIS IS JUST FOR TESTING
}

//not so hardcoded
async function createUser(setName: string, setEmail: string, setAge: number) {
	const user = await prisma.my_users.create({
		data: {
			name: setName,
			email: setEmail,
			age: setAge,
		},
	})
	return user
}

//hardcoded to find specifically something
async function findUser() {
	const user = await prisma.my_users.findMany({
		where: {
			name: "Bruno"
			// age_name: {
			// 	name: "Bruno",
			// 	age: 22,
			// }
		},
	})
	return user
}

async function main() {
	// await deleteAllUsers()//!THIS IS JUST FOR TESTING
	// await createUser("Bruno", "bruno@test.com", 22)//*creates single hardcoded user
	// await createUser("Miguel", "miguel@test.com", 45)
	// await findUser()

	const user = await prisma.my_users.findMany({
		where: {
			AND: [{ email: { endsWith: "2@test.com" } }, { name: "Bruno" } ],
		}
	})
	
	console.log(user.length)
	
}


main()
	.catch(e => {
		console.error(e.message)
	})
	.finally(async () => {
		await prisma.$disconnect()
	})









//todo check awaits

//create, needing to send as create({ data: {<object data as in table>}})
//createMany (btw, select wont work with this)
//findMany for all rows of a table
//deleteMany to delete everything of a table



//this goes in with all user data:
//	<other data like name>: (value)
// userPreference: {
// 	create: {
// 		emailUpdates: true,
// 	},
// },



//this goes in my_users.create({data:{}, <here>}): just gets a specific field or fields
//or also in findUnique({where:{data}, select <here> })
// select: {
// 	name: true,
// 	userPreference: { select: { id: true} },
// }

//{ log:["query"]} in PrismaClient(<here>) for logging query is everything that it is querying to db

//findUnique only works for @unique fields

//for the findMany: distinct, take, skip, orderBy, 			
//for the where: equals, not, in, lt (less than), gt (greater than), lte, gte, contains, endsWith, startsWith
//AND, OR, 

//distinct?
//take: <number> 	-> returns <number> of users
//skip: <number> 	-> skips in the list <number> of users
//oredrBy: <field> "asc"/"desc"